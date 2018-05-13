#ifndef TERRAIN_H
#define TERRAIN_H

#include <OBDEngine/OBDTerrain.h>

#include <Types.h>
#include <GraphicEngine/Texture.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Vector3.h>

class Terrain{
    public:
        Terrain(const char* heightMap);
        ~Terrain();

        void setTexture(Texture* terrainTexture, Texture* detailTexture);

        void setSize(Vector3<f32>);

        Vector3<f32> getPointCollision(Vector2<i32> cursor);

        f32 getY(f32, f32);

        /*scene::ITerrainSceneNode* getTerrain();*/
    private:
       OBDTerrain *t;

	   f32 yscale;
};

#endif