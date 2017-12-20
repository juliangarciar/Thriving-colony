#include "Terrain.h"
#include "Window.h"

using namespace irr;

Terrain::Terrain(const char* heightMap){
	Window *sc = Window::Instance();
    terrain = sc->getSceneManager()->addTerrainSceneNode(
		heightMap,
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 10.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
    );
    std::cout << sc->getSceneManager() << std::endl;
    selector = sc->getSceneManager()->createTerrainTriangleSelector(terrain);
    terrain->setTriangleSelector(selector);
    collisionManager = sc->getSceneManager()->getSceneCollisionManager();
}

Vector3<float> Terrain::getPointCollision(Mouse *cursor){
	core::position2d<s32> pos = cursor->getCursor()->getPosition();
	core::vector3df point;
	core::triangle3df triangle;
	scene::ISceneNode *node = 0;
    const core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(pos);
    if (collisionManager->getCollisionPoint (ray, selector, point, triangle, node)) {
		return Vector3<float>(point);
    }
	return Vector3<float>();
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture){
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, terrainTexture->getTexture());
	terrain->setMaterialTexture(1, detailTexture->getTexture());
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
}

float Terrain::getY(float x, float z) {
	float y = terrain -> getHeight(x, z);
	return y;
}

Terrain::~Terrain() {
    delete terrain;
    terrain = NULL;
}

scene::ITerrainSceneNode* Terrain::getTerrain(){
	return terrain;
}