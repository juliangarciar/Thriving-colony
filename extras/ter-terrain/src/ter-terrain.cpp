#include "ter-terrain.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float ter_util_vec3_module(glm::vec3 p, int Xaxis, int Yaxis, int Zaxis) {
  	return sqrtf(p.x * p.x * Xaxis + p.y * p.y * Yaxis + p.z * p.z * Zaxis);
}

TerTerrain::TerTerrain(){
	this->vertices = nullptr;
	this->glm_vertices = nullptr;
	this->heights = nullptr;
	this->indices = nullptr;
}

TerTerrain::~TerTerrain(){
	free(this->vertices);
	free(this->glm_vertices);
	free(this->heights);
	free(this->indices);
}

void TerTerrain::setHeightsFromTexture(const char *path, float y_offset, float y_scale, int step){
	int i_w, i_h, i_c;

	//Get image data
	unsigned char *data = stbi_load(
		path,
		&i_w, &i_h, &i_c,
		1
	);

	if (!data) {
		printf("Failed to load heightmap image %s.\n", path);
		exit(0);
	}
	
	uint8_t *pixels = (uint8_t *) data;

	//Generate heightmap
	this->width = i_w / step;
	this->depth = i_h / step;

	this->heights = (float*)malloc(this->width * this->depth * sizeof(float));

	float min_h = 0;
	float max_h = 0;
	for (int x = 0; x < this->width; x++) {
		for (int z = 0; z < this->depth; z++) {
			float h = pixels[(x * step) + (this->width * z)];

			/* Normalize height to [-1, 1] */ 
			h = h / 127.5 - 1.0f;

			/* Apply offset */
			h += y_offset;

			/* Apply scale */
			h *= y_scale;

			if (h < min_h) min_h = h;
			if (h > max_h) max_h = h;

			setHeightAt(x, z, h);
		}
	}
	
	this->height = max_h - min_h;

	free(data);
}

void TerTerrain::buildMesh(){
	//If this happens then the terrain is not visible
	if (this->width == 0 || this->depth == 0) {
		this->num_indices = 0;
		return;
	}

	int vertices_w = this->width;
	int vertices_d = this->depth;
	unsigned int num_indices = (this->width - 1) * (this->depth - 1) * 6;

	//Prepare memory
	this->vertices = (float*)malloc(vertices_w * vertices_d * 8 * sizeof(float)); //8 data per vertex
	this->glm_vertices = (glm::vec3*)malloc(vertices_w * vertices_d * sizeof(glm::vec3));
	this->num_vertices = 0;
	this->indices = (unsigned int*)malloc(num_indices * sizeof(unsigned int));

	/* Add each vertex in the grid. We are going to render using an index buffer
	* so we don't need to duplicate vertices, which reduces massively the
	* storage requirements for the vertex data, since terrains have high
	* vertex counts.
	*/
	unsigned int index = 0;
	for (int vx = 0; vx < vertices_w; vx++) {
		for (int vz = 0; vz < vertices_d; vz++) {
			float vy = TERRAIN(this, vx, vz);
			glm::vec3 n0 = calculate_normal(vx, vz);
			this->vertices[index++] = (float) vx;
			this->vertices[index++] = (float) vy;
			this->vertices[index++] = (float) vz;
			this->vertices[index++] = (float) n0.x;
			this->vertices[index++] = (float) n0.y;
			this->vertices[index++] = (float) n0.z;
			this->vertices[index++] = (float) vx / vertices_w;
			this->vertices[index++] = (float) vz / vertices_d;

			this->glm_vertices[this->num_vertices] = glm::vec3((float) vx, (float) vy, (float) vz);

			this->num_vertices++;
		}
	}

	/* Initialize the number of rendering indices so it covers the entire
	* terrain. */

	index = 0;
	for(int z = 0; z < (this->depth - 1); z++){
		for(int x = 0; x < this->width; x++){
			/* right */
			if(x != this->width - 1){
				this->indices[index++] = x + (z * this->width);
				this->indices[index++] = x + 1 + (z * this->width);
				this->indices[index++] = x + ((z + 1) * this->width);
			}
			/* left */
			if(x != 0){
				this->indices[index++] = x + (z * this->width);
				this->indices[index++] = x + ((z + 1) * this->width);
				this->indices[index++] = (x - 1) + ((z + 1) * this->width);
			}
		}
	}

	this->num_indices = index;

	assert(num_indices == this->num_indices);

	// TRIANGLES
	assert(this->num_indices % 3 == 0);

	this->triangled_indices.reserve(this->num_indices/3);
	this->triangle_centroids.reserve(this->num_indices/3);

	index = 0;
	for (int i = 0; i < this->num_indices; i += 3){
		//Triangle
		std::array<unsigned int, 3> temp_index = {{this->indices[i], this->indices[i+1], this->indices[i+2]}};
		this->triangled_indices.push_back(temp_index);

		//Centroid
		glm::vec3 v1 = this->glm_vertices[this->indices[i]];
		glm::vec3 v2 = this->glm_vertices[this->indices[i+1]];
		glm::vec3 v3 = this->glm_vertices[this->indices[i+2]];

		glm::vec3 b((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);

		this->triangle_centroids.push_back(b);
	}
}

glm::vec3 TerTerrain::calculate_normal(unsigned int x, unsigned int z) {
	assert((x >= 0 && x < this->width) && (z >= 0 && z < this->depth));
	if (x <= 0) x = 1;
	if (z <= 0) z = 1;
	if (x >= this->width-1) x = this->width-2;
	if (z >= this->depth-1) z = this->depth-2;
	float hl = TERRAIN(this, x - 1, z);
	float hr = TERRAIN(this, x + 1, z);
	float hd = TERRAIN(this, x, z + 1); /* Terrain expands towards -Z */
	float hu = TERRAIN(this, x, z - 1);
	glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);
	float m = ter_util_vec3_module(n, 1, 1, 1);
	if (m > 0) {
		n.x /= m;
		n.y /= m;
		n.z /= m;
	}
	return n;
}

void TerTerrain::setHeightAt(unsigned int x, unsigned int z, float h){
	assert((x >= 0 && x < this->width) && (z >= 0 && z < this->depth));

	TERRAIN(this, x, z) = h;
}

float TerTerrain::getHeightAt(unsigned int x, unsigned int z){
	assert((x >= 0 && x < this->width) && (z >= 0 && z < this->depth));
	
	return TERRAIN(this, x, z);
}