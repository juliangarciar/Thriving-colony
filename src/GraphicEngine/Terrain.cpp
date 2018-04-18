#include "Terrain.h"
#include "Window.h"
using namespace irr;

Terrain::Terrain(const char* heightMap) {
	Window *sc = Window::Instance();
    terrain = sc -> getSceneManager() -> addTerrainSceneNode(
		heightMap,
		0,										// parent node
		-1,										// node id
		core::vector3df(0.f, 0.f, 0.f),			// position
		core::vector3df(0.f, 0.f, 0.f),			// rotation
		core::vector3df(0, 0, 0),				// scale
		video::SColor ( 255, 255, 255, 255 ), 	// vertexColor
		2,										// maxLOD
		scene::ETPS_9,							// patchSize
		4										// smoothFactor
    );
    selector = sc -> getSceneManager() -> createTerrainTriangleSelector(terrain);
    terrain -> setTriangleSelector(selector);
    collisionManager = sc -> getSceneManager() -> getSceneCollisionManager();
}

Terrain::~Terrain() {
    terrain -> removeAll();
	terrain -> remove();
	delete terrain;
	delete selector;
	delete collisionManager;
	terrain = nullptr;
	selector = nullptr;
	collisionManager = nullptr;
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture) {
	terrain -> setMaterialTexture(0, terrainTexture -> getTexture());
	terrain -> setMaterialTexture(1, detailTexture -> getTexture());
	terrain -> setMaterialType(video::EMT_DETAIL_MAP);
    terrain -> scaleTexture(1.0f, 20.0f);
}

void Terrain::setSize(Vector3<f32> s){
	Window *sc = Window::Instance();
	terrain -> setScale(s.getVectorF());
	selector = sc -> getSceneManager() -> createTerrainTriangleSelector(terrain);
    terrain -> setTriangleSelector(selector);
    collisionManager = sc -> getSceneManager() -> getSceneCollisionManager();
}

Vector3<f32> Terrain::getPointCollision(Mouse *cursor){
	Vector2<i32> p = cursor -> getPosition();
	core::position2d<s32> pos = core::position2d<s32>(p.x, p.y);
	core::vector3df point;
	core::triangle3df triangle;
	scene::ISceneNode *node = 0;
    const core::line3d<f32> ray = collisionManager -> getRayFromScreenCoordinates(pos);
    if (collisionManager -> getCollisionPoint (ray, selector, point, triangle, node)) {
		return Vector3<f32>(point);
    }
	return Vector3<f32>();
}

f32 Terrain::getY(f32 x, f32 z) {
	return (f32)terrain -> getHeight(x, z);
}

scene::ITerrainSceneNode* Terrain::getTerrain() {
	return terrain;
}