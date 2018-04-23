#include "OBDTerrain.h"

OBDTerrain::OBDTerrain(std::string path){
	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	terrain = new ParseTerrain(256, 256, 1); // ToDo
	terrain ->generateMeshFromImage(path.c_str());

	generateTerrain();

	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);
}

OBDTerrain::OBDTerrain(OBDSceneNode* parent, std::string path){
	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	terrain = new ParseTerrain(256, 256, 1); // ToDo
	terrain ->generateMeshFromImage(path.c_str());

	generateTerrain();

	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);

	parent->addChild(this);
}

OBDTerrain::~OBDTerrain() {
	delete rotationNode;
	rotationNode = nullptr;
}

void OBDTerrain::generateTerrain(){
	int w = terrain->getTerrainWidth();
	int h = terrain->getTerrainHeight();
	int d = terrain->getTerrainDepth();

	mesh.boundingBox.min = glm::vec3(0,0,0);
	mesh.boundingBox.max = glm::vec3(w, h, h);
	mesh.boundingBox.size = glm::vec3(w, h, h);
	mesh.boundingBox.center = glm::vec3(w/2, h/2, h/2);
	
	mesh.name = "terrain";
	mesh.vbo = terrain->getTerrainVertices();
	mesh.indices = terrain->getTerrainIndices();

	material.ambientColor = glm::vec3(1,1,1);
}

void OBDTerrain::translate(f32 tX, f32 tY, f32 tZ) {
	TTransform* t = (TTransform*) translationNode -> getEntity();
	t -> translate(tX, tY, tZ);
	node_position += glm::vec3(tX, tY, tZ);
}

void OBDTerrain::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
	TTransform* t = (TTransform*) rotationNode -> getEntity();
	t -> rotate(rX, rY, rZ, angle);
	node_rotation += glm::vec3(rX, rY, rZ);
}

void OBDTerrain::scale(f32 sX, f32 sY, f32 sZ) {
	TTransform* t = (TTransform*) scaleNode -> getEntity();
	t -> scale(sX, sY, sZ);
	node_scale += glm::vec3(sX, sY, sZ);
}

void OBDTerrain::setPosition(glm::vec3 p) {
	TTransform* t = (TTransform*) translationNode -> getEntity();
	glm::vec3 o = node_position - p;
	t -> translate(o.x, o.y, o.z);
	node_position = p;
}

void OBDTerrain::setRotation(glm::vec3 r, f32 angle) {
	TTransform* t = (TTransform*) rotationNode -> getEntity();
	glm::vec3 o = node_rotation - r;
	t -> rotate(o.x, o.y, o.z, angle);
	node_rotation = r;
}

void OBDTerrain::setScale(glm::vec3 s) {
	TTransform* t = (TTransform*) scaleNode -> getEntity();
	glm::vec3 o = node_scale - s;
	t -> scale(o.x, o.y, o.z);
	node_scale = s;
}

void OBDTerrain::setActive(bool a) {
	terrainNode -> setActive(a);
}

bool OBDTerrain::getActive() {
	return terrainNode -> getActive();
}

TNode *OBDTerrain::getFirstNode(){
    return rotationNode;
}