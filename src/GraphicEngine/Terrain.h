#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <irrlicht.h>
#include "Texture.h"

using namespace irr;

class Terrain{
    public:
        Terrain(const char* heightMap);
        ~Terrain();

        void setTexture(Texture* terrainTexture, Texture* detailTexture);

        scene::ITerrainSceneNode* getTerrain();
    private:
        scene::ITerrainSceneNode* terrain;
        /*scene::ITriangleSelector* selector;
        scene::ISceneCollisionManager* collisionManager;
        scene::ISceneNode* sphere;
        core::position2d<s32> pos;
        core::vector3df point;
        core::triangle3df triangle;
        scene::ISceneNode *node;*/
};

#endif