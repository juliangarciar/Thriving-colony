#include "OBDTerrain.h"

OBDTerrain::OBDTerrain(std::string path){
	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	generateTerrain(path.c_str());

	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);
}

OBDTerrain::OBDTerrain(OBDSceneNode* parent, std::string path){
	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	generateTerrain(path.c_str());

	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);

	parent->addChild(this);
}

OBDTerrain::~OBDTerrain() {
	delete rotationNode;
	rotationNode = nullptr;
}

void OBDTerrain::generateTerrain(const char *path){
	// ToDo: revisar parametros
	terrain = ter_terrain_new();
	ter_terrain_set_heights_from_texture(terrain, path, -0.5, 100, 1);
	ter_terrain_build_mesh(terrain);

	//Mesh
	int w = terrain->width;
	int h = terrain->height;
	int d = terrain->depth;

	mesh.boundingBox.min = glm::vec3(0,0,0);
	mesh.boundingBox.max = glm::vec3(w, h, d);
	mesh.boundingBox.size = glm::vec3(w, h, d);
	mesh.boundingBox.center = glm::vec3(w/2, h/2, d/2);
	
	mesh.name = "terrain";
	mesh.vbo = std::vector<f32>(terrain->vertices, terrain->vertices+(terrain->num_vertices*8));
	mesh.indices = std::vector<u32>(terrain->indices, terrain->indices+terrain->num_indices);

	//Material
	material.ambientColor = glm::vec3(1,1,1);
	material.diffuseColor = glm::vec3(1,1,1);
	material.specularColor = glm::vec3(1,1,1);
	material.specularExponent = 90;

	//Octree
	vertex_vector = std::vector<glm::vec3>(terrain->glm_vertices, terrain->glm_vertices + terrain->num_vertices);

	octree = new SDF(vertex_vector, terrain->triangled_indices, terrain->triangle_centroids);
	octree->init();
	octree->build();
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
	TMesh* t = (TMesh*) terrainNode -> getEntity();
	return t;
}

void OBDTerrain::setTexture(OBDTexture* t){
    TMesh* m = (TMesh*) terrainNode -> getEntity();
    m -> setTexture(t->getType(), t->getTexture());
}

TMesh *OBDTerrain::getTerrainMesh(){
	TMesh* t = (TMesh*) terrainNode -> getEntity();
	return t;
}

TNode *OBDTerrain::getFirstNode(){
    return rotationNode;
}

f32 OBDTerrain::getY(f32 x, f32 z){
	OBDLine line;
	line.start = glm::inverse(getTerrainMesh()->getModelMatrix()) * glm::vec4(glm::vec3(x, -10000, z), 1); //ToDo: Revisar
	line.end = glm::inverse(getTerrainMesh()->getModelMatrix()) * glm::vec4(glm::vec3(x, 10000, z), 1); //ToDo: Revisar
	glm::vec3 dir = glm::normalize(line.end - line.start);
	std::vector<glm::vec3> res = octree->query(line.start, dir);

	if (res.size() > 0) {
		glm::vec4 r(res[0], 1);
		r = getTerrainMesh()->getModelMatrix() * r;
		return r.y;
	}
	return 0;
}

glm::vec3 OBDTerrain::getRayCollision(OBDLine line){
	glm::vec3 dir = glm::normalize(line.end - line.start);
	std::vector<glm::vec3> res = octree->query(line.start, dir);
	if (res.size() > 0) {
		glm::vec4 r(res[0], 1);
		return (getTerrainMesh()->getModelMatrix() * r);
	}
	return glm::vec3();
}