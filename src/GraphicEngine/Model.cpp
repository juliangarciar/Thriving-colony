#include "Model.h"
#include "Window.h"

Model::Model(i32 id, std::string path) {
   obj = Window::Instance()->getEngine()->createObject(id, path, true);
   std::cout << "Se ha cargado un edificio " << path << std::endl;
   materials = obj->getMaterials();
}

Model::Model(SceneNode *parent, i32 id, std::string path) {
   obj = Window::Instance()->getEngine()->createObject(parent->getSceneNode(), id, path, true);
   std::cout << "Se ha cargado un edificio " << path << std::endl;
   materials = obj->getMaterials();
}

Model::~Model() {
	delete obj;
	obj = nullptr;
}

void Model::setID(i32 id) {
    //En nuestro motor no se puede
}

void Model::setPosition(Vector3<f32> pos) {
	if (pos.z > 0) pos.z *= -1;
    obj->setPosition(glm::vec3(pos.x, pos.y, pos.z));
	obj->refreshModelMatrix(glm::mat4(1.0f));
	obj->refreshBoundingBox();
}

void Model::setRotation(Vector3<f32> r) {
	obj->setRotation(glm::vec3(r.x, r.y, r.z));
	obj->refreshBoundingBox();
}

void Model::setScale(Vector3<f32> s) {
    obj->setScale(glm::vec3(s.x, s.y, s.z));
	obj->refreshModelMatrix(glm::mat4(1.0f));
	obj->refreshBoundingBox();
}

void Model::setActive(bool a) {
    obj->setActive(a);
}

void Model::setMaterial(Material *m) {
    //ToDo
}

void Model::setColor(Color c) {
	for (std::map<std::string, OBDMaterial*>::iterator it = materials->begin(); it != materials->end(); ++it) {
		it->second->setDiffuseColor(OBDColor(c.r/255, c.g/255, c.b/255, c.a/255));
	}
}

Vector3<f32> Model::getPosition() {
    return Vector3<f32>(obj->getPosition().x, obj->getPosition().y, -obj->getPosition().z);
}

Vector3<f32> Model::getRotation() {
    return Vector3<f32>(obj -> getRotation().x, obj -> getRotation().y, obj -> getRotation().z);
}

i32 Model::getID() {
    return obj->getID();
}