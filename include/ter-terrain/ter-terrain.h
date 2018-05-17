#ifndef __TER_TERRAIN_H__
#define __TER_TERRAIN_H__

#include <array>
#include <vector>
#include <glm/glm.hpp>

/* We need a large enough index buffer to:
 *
 * 1. Ensure that we have room for the worse case scenario (all indices)
 * 2. Avoid stalling the GPU with updates to the index buffer.
 *
 * So we use two buffers that are twice the size of the worse case scenario.
 */

#define TERRAIN(t, w, d) t->heights[(w) * t->depth + (d)]

class TerTerrain {
	public:
		TerTerrain();
		~TerTerrain();

		void setHeightsFromTexture(const char *path, float y_offset, float y_scale, int step);
		void buildMesh();
		void setHeightAt(unsigned int x, unsigned int z, float h);
		float getHeightAt(unsigned int x, unsigned int z);

		int width, height, depth;
		
		float *heights;

		float *vertices;
		glm::vec3 *glm_vertices;
		unsigned int num_vertices;

		unsigned int *indices;
		unsigned int num_indices;

		std::vector< std::array<unsigned int, 3> > triangled_indices;
		std::vector<glm::vec3> triangle_centroids;
	private:
		glm::vec3 calculate_normal(unsigned int x, unsigned int z);
};

#endif
