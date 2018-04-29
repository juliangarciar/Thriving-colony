#include "Terrain.h"
#include "Window.h"

//ToDo: no deberian haber datos aqui
Terrain::Terrain(const char* heightMap) {
	//t = Window::Instance()->getEngine()->createTerrain(heightMap);
}

Terrain::~Terrain() {
	
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture) {
	
}

void Terrain::setSize(Vector3<f32> s){
	//t->setScale(glm::vec3(s.x, s.y, s.z));
}

Vector3<f32> Terrain::getPointCollision(Mouse *cursor){
	
	return Vector3<f32>(8000,0,8000);
}

f32 Terrain::getY(f32 x, f32 z) {
	return 0;
}

/*scene::ITerrainSceneNode* Terrain::getTerrain() {
	return terrain;
}*/