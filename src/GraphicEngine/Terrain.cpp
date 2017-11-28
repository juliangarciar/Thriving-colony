#include "Terrain.h"
#include "Screen.h"

using namespace irr;

Terrain::Terrain(const char* heightMap){
	Screen *sc = Screen::Instance();
    terrain = sc->getSceneManager()->addTerrainSceneNode(
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

    selector = sc->getSceneManager()->createTerrainTriangleSelector(terrain);
    terrain->setTriangleSelector(selector);
    collisionManager = sc->getSceneManager()->getSceneCollisionManager();
    //sphere = Screen::Instance()->getSceneManager()->addSphereSceneNode();
	

	std::cout << "Terrain: " << terrain->getBoundingBox().getArea() << std::endl;
}

Vector3<float> Terrain::getPointCollision(Mouse *cursor){
	core::position2d<s32> pos = cursor->getCursor()->getPosition();
	core::vector3df point;
	core::triangle3df triangle;
	scene::ISceneNode *node = 0;
    const core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(pos);
    if (collisionManager->getCollisionPoint (ray, selector, point, triangle, node)) {
        //sphere->setPosition(point);
		return Vector3<float>(point);
    }
	return Vector3<float>();
}

/*void Terrain::getTriangleCollision(Mouse *cursor){
	core::position2d<s32> pos = cursor->getCursor()->getPosition();
	core::vector3df point;
	core::triangle3df triangle;
	scene::ISceneNode *node = 0;
    const core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(pos);
    if (collisionManager->getCollisionPoint (ray, selector, point, triangle, node)) {
        //std::cout << triangle.pointA.X << " " << triangle.pointA.Y << " " << triangle.pointA.Z << std::endl;
        //std::cout << triangle.pointB.X << " " << triangle.pointB.Y << " " << triangle.pointB.Z << std::endl;
        //std::cout << triangle.pointC.X << " " << triangle.pointC.Y << " " << triangle.pointC.Z << std::endl;
    }
}*/

void Terrain::setTexture(Texture* terrainTexture, Texture* detailTexture){
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, terrainTexture->getTexture());
	terrain->setMaterialTexture(1, detailTexture->getTexture());
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
}

Terrain::~Terrain() {
    delete terrain;
    terrain = NULL;
}

scene::ITerrainSceneNode* Terrain::getTerrain(){
	return terrain;
}