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
    private:
        scene::ITerrainSceneNode* terrain;
};

#endif