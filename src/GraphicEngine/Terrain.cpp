#include "Terrain.h"
#include "Window.h"

//ToDo: no deberian haber datos aqui
Terrain::Terrain(const char* heightMap) {
	t = Window::Instance()->getEngine()->createTerrain(heightMap, 1, 100, 1);
	t->rotate(glm::vec3(0, 1, 0), 180);
	t->translate(glm::vec3(256, 0, 0));
	t->refreshModelMatrix(glm::mat4(1.0f));
	terrainTex = nullptr;
	detailTex = nullptr;
}

Terrain::~Terrain() {
	delete t;
	t = nullptr;
	if (terrainTex != nullptr) delete terrainTex;
	if (detailTex != nullptr) delete detailTex;
}

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture) {
	t->setTexture(terrainTexture->getTexture());
}

void Terrain::setSize(Vector3<f32> s) {
	t->setScale(glm::vec3(s.x, s.y, s.z));
	t->refreshModelMatrix(glm::mat4(1.0f));
}

Vector3<f32> Terrain::getPointCollision(Vector2<i32> cursor) {
	OBDLine l = Window::Instance()->getEngine()->getRaycastFromScreenCoordinates(glm::vec2(cursor.x, cursor.y));
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