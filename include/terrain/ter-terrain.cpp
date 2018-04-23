#include "ter-terrain.h"

float ter_util_vec3_module(glm::vec3 p, int Xaxis, int Yaxis, int Zaxis) {
	return sqrtf(p.x * p.x * Xaxis + p.y * p.y * Yaxis + p.z * p.z * Zaxis);
}
void ter_util_vec3_normalize(glm::vec3 *p) {
	float m = ter_util_vec3_module(*p, 1, 1, 1);
	if (m > 0) {
		p->x /= m;
		p->y /= m;
		p->z /= m;
	}
}

TerTerrain::TerTerrain(unsigned width, unsigned depth, unsigned step){
	this->width = width;
	this->depth = depth;
	this->step = step;
	this->height = (float*)std::malloc(sizeof(float) * width * depth); 
}

void TerTerrain::generateMeshFromBuffer(unsigned char *img, int width, int height, int channels){
	if (channels != 1){
		std::cout << "El mapa de bits debe tener ser en escala de grises (1 canal - 8 bits)" << std::endl;
		exit(0);
	}

	this->data = img;
	this->img_width = width;
	this->img_height = depth;
	this->img_channels = channels;

	ter_terrain_set_heights_from_texture();
	ter_terrain_build_mesh();
}

void TerTerrain::ter_terrain_set_height(unsigned w, unsigned d, float h) {
	TERRAIN(this, w, d) = h;
}

void TerTerrain::ter_terrain_set_heights_from_texture(){
	uint8_t *pixels = (uint8_t *) data;

	for (int x = 0; x < width; x++) {
		for (int z = 0; z < depth; z++) {
			float h = pixels[img_height * z + x];

			/* Normalize height to [-1, 1] */ 
			h = h / 127.5 - 1.0f;

			ter_terrain_set_height(x, z, h);
		}
	}
}

glm::vec3 TerTerrain::calculate_normal(unsigned x, unsigned z){
	if (x == 0) x = 1;
	if (z == 0) z = 1;
	float hl = TERRAIN(this, x - 1, z);
	float hr = TERRAIN(this, x + 1, z);
	float hd = TERRAIN(this, x, z + 1); /* Terrain expands towards -Z */
	float hu = TERRAIN(this, x, z - 1);
	glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);
	ter_util_vec3_normalize(&n);
	return n;
}

void TerTerrain::compute_indices_for_clip_volume(TerClipVolume *clip) {
	int min_col = MAX(MIN(clip->x0 / step, width - 2), 0);
	int max_col = MAX(MIN((clip->x1 + step) / step, width - 2), 0);

	/* Z1 is always largest, because our terrain grows towrds -Z, it means that
	* it defines the min_row
	*/
	int min_row = MAX(MIN(-clip->z1 / step, depth - 1), 0);
	int max_row = MAX(MIN(- (clip->z0 - step) / step, depth - 1), 0);

	/* If this happens then the terrain is not visible */
	if (min_col == max_col || min_row == max_row) {
		num_indices = 0;
		return;
	}

	unsigned index = 0;
	for (int c = min_col; c <= max_col; c++) {
		for (int r = min_row; r <= max_row; r++) {
		 /* If this is not the first strip then we need to produce a degenerate
			* link with the previous strip using the first vertex from this strip
			* and the last vertex from the last before we start recording the
			* new strip. Here is the first vertex of this strip.
			*/
		 if (c > min_col && r == min_row)
			indices[index++] = c * depth + r;

		 indices[index++] = c * depth + r;
		 indices[index++] = (c + 1) * depth + r;

		 /* Link the next triangle strip using degenerate triangles. For that
			* we need to duplicate the last vertex of this strip and the first
			* vertex of the next.
			*/
		 if (r == max_row && c < max_col)
			indices[index++] = (c + 1) * depth + r;
		}
	}

	num_indices = index;
}

void TerTerrain::ter_terrain_build_mesh() {
	/* GL's +Z axis goes towards the camera, so make the terrain's Z coordinates
	* negative so that larger (negative) Z coordinates are more distant.
	*/

	int vertices_w = width;
	int vertices_d = depth;

	/* Add each vertex in the grid. We are going to render using an index buffer
	* so we don't need to duplicate vertices, which reduces massively the
	* storage requirements for the vertex data, since terrains have high
	* vertex counts.
	*/
	for (int vx = 0; vx < vertices_w; vx++) {
		for (int vz = 0; vz < vertices_d; vz++) {
			float vy = TERRAIN(this, vx, vz);
			glm::vec3 v0 = glm::vec3(vx * step, vy, -vz * step);
			glm::vec3 n0 = calculate_normal(vx, vz);

			vertices.push_back(v0);
			normals.push_back(n0);
		}
	}

	/* Build the indices to render the terrain using a single triangle strip
	* (using degenerate triangles) since that yields much better performance
	* than rendering triangles.
	*/
	unsigned num_indices = (vertices_w - 1) * (vertices_d * 2) + (vertices_w - 2) + (vertices_d - 2);
	indices = (unsigned*)std::malloc(sizeof(unsigned) * num_indices);

	/* Initialize the number of rendering indices so it covers the entire
	* terrain.
	*/
	TerClipVolume clip;
	clip.x0 = 0.0f;
	clip.x1 = (width - 1) * step;
	clip.z1 = 0.0f;
	clip.z0 = -(depth - 1) * step;
	compute_indices_for_clip_volume(&clip);

	assert(num_indices == num_indices);
}

float TerTerrain::ter_terrain_get_height_at(float x, float z) {
	/* Terrain's Z extends towards -Z, but our vertices need positive numbers */
	z = -z;

	/* Find offsets of the coords into a terrain quad */
	float offx = fmodf(x, step);
	float offz = fmodf(z, step);

	/* Compute the plane equation for the triangle we are in */
	glm::vec3 p1, p2, p3;
	float A, B, C, D;
	if (offx + offz <= step) {
		/* First triangle in the quad */
		p1.x = trunc(x / step);
		p1.z = trunc(z / step);
		p1.y = TERRAIN(this, (int)p1.x, (int)p1.z);

		p2.x = trunc(x / step) + 1;
		p2.z = trunc(z / step);
		p2.y = TERRAIN(this, (int)p2.x, (int)p2.z);

		p3.x = trunc(x / step);
		p3.z = trunc(z / step) + 1;
		p3.y = TERRAIN(this, (int)p3.x, (int)p3.z);
	} else {
		/* Second triangle in the quad */
		p1.x = trunc(x / step) + 1;
		p1.z = trunc(z / step);
		p1.y = TERRAIN(this, (int)p1.x, (int)p1.z);

		p2.x = trunc(x / step);
		p2.z = trunc(z / step) + 1;
		p2.y = TERRAIN(this, (int)p2.x, (int)p2.z);

		p3.x = trunc(x / step) + 1;
		p3.z = trunc(z / step) + 1;
		p3.y = TERRAIN(this, (int)p3.x, (int)p3.z);
	}

	/* Above we compute X,Z coords as vertex indices so we could use TERRAIN()
	* to compute heights at specific vertices, but to apply the plane equation
	* we need to turn the coordinates into world units
	*/
	p1.x *= step;
	p1.z *= step;
	p2.x *= step;
	p2.z *= step;
	p3.x *= step;
	p3.z *= step;

	/* FIXME: we probably want to pre-compute plane equations for each
	* triangle in the terrain rather than recomputing them all the time
	*/
	A = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
	B = (p2.z - p1.z) * (p3.x - p1.x) - (p3.z - p1.z) * (p2.x - p1.x);
	C = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	D = -(A * p1.x + B * p1.y + C * p1.z);

	/* Use the plane equation to find Y given (X,Z) */
	return (-D - C * z - A * x) / B;
}

void TerTerrain::ter_terrain_compute_clipped_indices(TerClipVolume *clip, unsigned *count, size_t *offset) {
	/* Our terrian indices cover terrain rendering by columns, so compute
	* how many columns in the vertex grid are to be cliped at the start
	* and the end of the terrain based on the x0/x1 dimensions of the clip
	* volume
	*/
	int min_col = MAX(MIN(clip->x0 / step, width), 0);
	int max_col = MAX(MIN((clip->x1 + step) / step, width - 2), 0);

	/* For each column in the terrain, we render 2 * depth vertices, plus
	* 2 extra vertices to produce a degenerate triangle so we can join the
	* strip for the next column.
	*/
	int indices_per_col = 2 * depth + 2;

	/* Compute how many indices we need to skip at the start of the index buffer
	* to start rendering at "min_col" and how many indices we can skip at
	* the tail of the buffer index to stop rendering at "max_col". Also, notice
	* that the last column we render has index "width - 2" and that for that
	* column we don't have those 2 extra indices to produce a degenerate (since
	* that is the last strip to render).
	*/
	int clipped_indices_start = min_col * indices_per_col;
	int clipped_indices_end =
		MAX(0, ((width - 2) - max_col) * indices_per_col - 2);

	*offset = min_col * indices_per_col * sizeof(int);
	*count = num_indices - clipped_indices_start - clipped_indices_end;
}

std::vector<glm::vec3> TerTerrain::getTerrainVertices(){
	return vertices;
}

std::vector<glm::vec3> TerTerrain::getTerrainNormals(){
	return normals;
}

float TerTerrain::getTerrainWidth() {
	return step * (width - 1);
}

float TerTerrain::getTerrainHeight() {
	return step * (depth - 1);
}
