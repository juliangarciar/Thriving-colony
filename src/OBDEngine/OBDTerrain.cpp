#include "OBDTerrain.h"

#define EPSILON 0.0005

OBDTerrain::OBDTerrain(OBDSceneNode* parent, std::string path, f32 y_offset, f32 y_scale, i32 step) : OBDEntity(parent) {
	//Generate terrainmesh
	terrain = new TerTerrain();
	terrain->setHeightsFromTexture(path.c_str(), y_offset, y_scale, step);
	terrain->buildMesh();

	vbo = new std::vector<f32>(terrain->vertices, terrain->vertices+(terrain->num_vertices*8));
	ibo = new std::vector<u32>(terrain->indices, terrain->indices+terrain->num_indices);

	//Octree
	vertex_vector = std::vector<glm::vec3>(terrain->glm_vertices, terrain->glm_vertices + terrain->num_vertices);

	octree = new SDF(vertex_vector, terrain->triangled_indices, terrain->triangle_centroids);
	octree->init();
	octree->build();

	//glslMesh
	mesh = new glslMesh();

	mesh -> num_indices = ibo -> size();

	glGenVertexArrays(1, &mesh->VAO);
	glGenBuffers(1, &vboid);
	glGenBuffers(1, &iboid);

	glBindVertexArray(mesh->VAO);

	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, vbo->size() * sizeof(f32), vbo -> data(), GL_STATIC_DRAW);  

	// load data into index buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo -> size() * sizeof(u32), ibo -> data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(3 * sizeof(f32)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET((3 + 3) * sizeof(f32)));
	
	glBindVertexArray(0);

	//Empty material
	material = new OBDMaterial();

	//Create Node
	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);
}

OBDTerrain::~OBDTerrain() {
	delete terrain;
	delete octree;
	delete mesh;
	delete material;
	vbo->clear();
	delete vbo;
	ibo->clear();
	delete ibo;

	terrain = nullptr;
	octree = nullptr;
	mesh = nullptr;
	material = nullptr;
	vbo = nullptr;
	ibo = nullptr;
}

void OBDTerrain::refreshModelMatrix(glm::mat4 parent) {
	parent_model_matrix = parent;
	TTransform* r = (TTransform*) rotationNode -> getEntity();
	TTransform* t = (TTransform*) translationNode -> getEntity();
	TTransform* s = (TTransform*) scaleNode -> getEntity();
	model_matrix = s->getMatrix() * t->getMatrix() * r->getMatrix() * parent;
	inverse_model_matrix = glm::inverse(model_matrix);
}

void OBDTerrain::setTexture(OBDTexture* t) {
    TMesh* m = (TMesh*) terrainNode -> getEntity();
    m -> getMaterial() -> setTexture(t);
}

TMesh *OBDTerrain::getTerrainMesh() {
	TMesh* t = (TMesh*) terrainNode -> getEntity();
	return t;
}

f32 OBDTerrain::getY(f32 x, f32 z) {
	OBDLine line;
	line.start = inverse_model_matrix * glm::vec4(glm::vec3(x+EPSILON, -10000, z+EPSILON), 1); //ToDo: Revisar
	line.end = inverse_model_matrix * glm::vec4(glm::vec3(x+EPSILON, 10000, z+EPSILON), 1); //ToDo: Revisar

	glm::vec3 world_dir = glm::normalize(line.end - line.start);
	std::vector<glm::vec3> res = octree->query(line.start, world_dir);

	if (res.size() > 0) {
		glm::vec4 r(res[0], 1);
		r = model_matrix * r;
		return r.y;
	}

	return 0;
}

glm::vec3 OBDTerrain::getRayCollision(OBDLine line) {
	line.start = inverse_model_matrix * glm::vec4(line.start, 1);
	line.end = inverse_model_matrix * glm::vec4(line.end, 1);

	glm::vec3 world_dir = glm::normalize(line.end - line.start);
	std::vector<glm::vec3> res = octree->query(line.start, world_dir);
	
	if (res.size() > 0) {
		glm::vec4 r(res[0], 1);
		r = model_matrix * r;
		return r;
	}

	return glm::vec3();
}