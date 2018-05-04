#ifndef __DRV_TERRAIN_H__
#define __DRV_TERRAIN_H__

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

typedef struct {
   float x0, y0, z0;
   float x1, y1, z1;
} TerClipVolume;

typedef struct {
   int width, height, depth;
   
   float step;
   
   float *heights;

   float *vertices;
   glm::vec3 *glm_vertices;
   unsigned int num_vertices;

   unsigned int *indices;
   unsigned int num_indices;

   std::vector< std::array<unsigned int, 3> > triangled_indices;
   std::vector<glm::vec3> triangle_centroids;
} TerTerrain;

TerTerrain *ter_terrain_new(unsigned int width, unsigned int depth, float step);
void ter_terrain_free(TerTerrain *t);

void ter_terrain_set_height(TerTerrain *t, unsigned int w, unsigned int d, float h);

float ter_terrain_get_height_at(TerTerrain *t, float x, float z);

void ter_terrain_set_heights_from_texture(TerTerrain *t, const char *path, float offset, float scale);
   
void ter_terrain_build_mesh(TerTerrain *t);

void ter_terrain_compute_clipped_indices(TerTerrain *t, TerClipVolume *clip,
                                         unsigned int *count, size_t *offset);

float ter_terrain_get_width(TerTerrain *t);
float ter_terrain_get_height(TerTerrain *t);
float ter_terrain_get_depth(TerTerrain *t);

#endif
