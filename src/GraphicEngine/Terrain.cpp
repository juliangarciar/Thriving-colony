#include "Terrain.h"
#include "Screen.h"

using namespace irr;

Terrain::Terrain(const char* heightMap){
    terrain = Screen::Instance()->getSceneManager()->addTerrainSceneNode(
		heightMap,
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
    );
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture){
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, terrainTexture->getTexture());
	terrain->setMaterialTexture(1, detailTexture->getTexture());
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
}

scene::ITerrainSceneNode* Terrain::getTerrain(){
	return terrain;
}