#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <irrlicht.h>
#include <IOEngine/Mouse.h>
#include "Texture.h"
#include "Vector3.h"

using namespace irr;

class Terrain{
    public:
        Terrain(const char* heightMap);
        ~Terrain();

        void setTexture(Texture* terrainTexture, Texture* detailTexture);

        Vector3<float> getPointCollision(Mouse *cursor);

        scene::ITerrainSceneNode* getTerrain();

        float getY(float, float);
    private:
        scene::ITerrainSceneNode* terrain;
        scene::ITriangleSelector* selector;
        scene::ISceneCollisionManager* collisionManager;
        //scene::ISceneNode* sphere;
};

#endif