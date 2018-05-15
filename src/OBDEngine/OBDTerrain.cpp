#include "OBDTerrain.h"

#define EPSILON 0.0005

OBDTerrain::OBDTerrain(OBDSceneNode* parent, std::string path, f32 y_offset, f32 y_scale, i32 step) : OBDEntity(parent) {
	glslMesh *mesh = new glslMesh();
	OBDMaterial *material = new OBDMaterial();

	//Generate mesh and material
	terrain = new TerTerrain();
	terrain->setHeightsFromTexture(path.c_str(), y_offset, y_scale, step);
	terrain->buildMesh();

	//Mesh
	i32 w = terrain->width;
	i32 h = terrain->height;
	i32 d = terrain->depth;

	mesh -> vbo = std::vector<f32>(terrain->vertices, terrain->vertices+(terrain->num_vertices*8));
	mesh -> ibo = std::vector<u32>(terrain->indices, terrain->indices+terrain->num_indices);

	//Octree
	vertex_vector = std::vector<glm::vec3>(terrain->glm_vertices, terrain->glm_vertices + terrain->num_vertices);

	octree = new SDF(vertex_vector, terrain->triangled_indices, terrain->triangle_centroids);
	octree->init();
	octree->build();

	terrainNode = new TNode(new TMesh(mesh, material), scaleNode);
}

OBDTerrain::~OBDTerrain() {
	delete terrain;
	delete octree;

	terrain = nullptr;
	octree = nullptr;
}

void OBDTerrain::setTexture(OBDTexture* t){
    TMesh* m = (TMesh*) terrainNode -> getEntity();
    m -> getMaterial() -> setTexture(t);
}

TMesh *OBDTerrain::getTerrainMesh(){
	TMesh* t = (TMesh*) terrainNode -> getEntity();
	return t;
}

f32 OBDTerrain::getY(f32 x, f32 z){
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

glm::vec3 OBDTerrain::getRayCollision(OBDLine line){

	/*std::cout << "----------" << std::endl;
	for (i32 i = 0; i < 4; i++){
		for (i32 j = 0; j < 4; j++){
			std::cout << inverse_model_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;*/

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