#ifndef PARSETERRAIN_H
#define PARSETERRAIN_H

#include <cstdint>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <vector>
#include <cfloat>
#include <float.h>
#include <cmath>
#include <math.h>
#include <glm/glm.hpp>

/* We need a large enough index buffer to:
 *
 * 1. Ensure that we have room for the worse case scenario (all indices)
 * 2. Avoid stalling the GPU with updates to the index buffer.
 *
 * So we use two buffers that are twice the size of the worse case scenario.
 */
#define TERRAIN_NUM_INDEX_BUFFERS 3
#define TERRAIN(t, w, d) t->heights[(w) * t->depth + (d)]

#define MAX fmaxf
#define MIN fminf

typedef struct {
   float x0, x1, y0, y1, z0, z1;
} ClipVolume;

class ParseTerrain {
	public:
		ParseTerrain(unsigned width, unsigned depth, unsigned step);
		~ParseTerrain();

		void generateMeshFromImage(const char *path);

		void generateMeshFromBuffer(unsigned char *img, int width, int height, int channels);

		std::vector<float> getTerrainVertices();

		unsigned int getVertexNumber();

		std::vector<unsigned short> getTerrainIndices();

		float getTerrainWidth();
		float getTerrainHeight();
		float getTerrainDepth();
	private:
		void terrain_set_height(unsigned w, unsigned d, float h);
		void terrain_set_heights_from_texture();
		glm::vec3 calculate_normal(unsigned x, unsigned z);
		void compute_indices_for_clip_volume(ClipVolume *clip);
		void terrain_build_mesh();

		int width, height, depth;
		float step;

		unsigned char *data;
		int img_width, img_height, img_channels;

		float *heights;

		std::vector<float> vertices;

		unsigned int num_vertices;

		std::vector<unsigned short> indices;
		unsigned short num_indices;
};

#endif
