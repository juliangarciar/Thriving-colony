#include "Terrain.h"
#include "Window.h"

//ToDo: no deberian haber datos aqui
Terrain::Terrain(const char* heightMap) {
	t = Window::Instance()->getEngine()->createTerrain(heightMap);
	//t->rotate(0, 1, 0, 270.f);
	//t->rotate(0, 0, 1, 180.f);
	//t->translate(0, 0, -256);
}

Terrain::~Terrain() {
	
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture) {
	
}

void Terrain::setSize(Vector3<f32> s){
	t->setScale(glm::vec3(s.x, s.y, s.z));
}

Vector3<f32> Terrain::getPointCollision(Mouse *cursor){
	OBDLine l = Window::Instance()->getEngine()->getRelativeRaycastFromScreenCoordinates(glm::vec2(cursor->getPosition().x, cursor->getPosition().y), t->getTerrainMesh()->getModelMatrix());
	glm::vec3 c = t->getRayCollision(l);
	return Vector3<f32>(c.x, c.y, c.z);
}

f32 Terrain::getY(f32 x, f32 z) {
	return t->getY(x, z);
}

/*scene::ITerrainSceneNode* Terrain::getTerrain() {
	return terrain;
}*/