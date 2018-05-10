#include "Terrain.h"
#include "Window.h"

//ToDo: no deberian haber datos aqui
Terrain::Terrain(const char* heightMap) {
	t = Window::Instance()->getEngine()->createTerrain(heightMap);
	t->translate(-256, 0, 0);
}

Terrain::~Terrain() {
	delete t;
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture) {
	t->setTexture(terrainTexture->getTexture());
}

void Terrain::setSize(Vector3<f32> s){
	t->setScale(glm::vec3(s.x, s.y, s.z));
}

Vector3<f32> Terrain::getPointCollision(Mouse *cursor){
	OBDLine l = Window::Instance()->getEngine()->getRelativeRaycastFromScreenCoordinates(glm::vec2(cursor->getPosition().x, cursor->getPosition().y), t->getTerrainMesh()->getModelMatrix());
	glm::vec3 c = t->getRayCollision(l);
	return Vector3<f32>(c.x, c.y, -c.z);
}

f32 Terrain::getY(f32 x, f32 z) {
	if (z > 0) z *= -1;
	f32 y = t->getY(x, z);
	return y;
}

/*scene::ITerrainSceneNode* Terrain::getTerrain() {
	return terrain;
}*/