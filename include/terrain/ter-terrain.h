#ifndef TERRAIN_H__
#define TERRAIN_H__

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
#define TER_TERRAIN_NUM_INDEX_BUFFERS 3
#define TERRAIN(t, w, d) t->height[(w) * t->depth + (d)]

#define MAX fmaxf
#define MIN fminf

typedef struct {
   float x0, x1, y0, y1, z0, z1;
} TerClipVolume;

class TerTerrain {
	public:
		TerTerrain(unsigned width, unsigned depth, unsigned step);
		~TerTerrain();

		void generateMeshFromBuffer(unsigned char *img, int width, int height, int channels);

		std::vector<glm::vec3> getTerrainVertices();
		std::vector<glm::vec3> getTerrainNormals();

		float getTerrainWidth();
		float getTerrainHeight();

		//EXTRA
		float ter_terrain_get_height_at(float x, float z);
		void ter_terrain_compute_clipped_indices(TerClipVolume *clip, unsigned *count, size_t *offset);
	private:
		void ter_terrain_set_height(unsigned w, unsigned d, float h);
		void ter_terrain_set_heights_from_texture();
		glm::vec3 calculate_normal(unsigned x, unsigned z);
		void compute_indices_for_clip_volume(TerClipVolume *clip);
		void ter_terrain_build_mesh();

		int width, depth;
		float step;

		unsigned char *data;
		int img_width, img_height, img_channels;

		float *height;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;

		unsigned *indices;
		unsigned num_indices;

		unsigned vao;
		unsigned vertex_buf;

		unsigned index_buf[TER_TERRAIN_NUM_INDEX_BUFFERS];
		unsigned ibuf_idx;
		unsigned ibuf_used;
		unsigned ibuf_cur_offset;

		glm::mat4 prev_mvp;
		bool prev_mvp_valid;
};

#endif
