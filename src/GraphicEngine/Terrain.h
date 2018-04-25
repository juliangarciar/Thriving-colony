#ifndef TERRAIN_H
#define TERRAIN_H

#include <Types.h>
#include <IOEngine/Mouse.h>
#include <GraphicEngine/Texture.h>
#include <MathEngine/Vector3.h>

class Terrain{
    public:
        Terrain(const char* heightMap);
        ~Terrain();

        void setTexture(Texture* terrainTexture, Texture* detailTexture);

        void setSize(Vector3<f32>);

        Vector3<f32> getPointCollision(Mouse *cursor);

        /*scene::ITerrainSceneNode* getTerrain();*/

        f32 getY(f32, f32);
    private:
       
	   
};

#endif