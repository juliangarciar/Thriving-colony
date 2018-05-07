#include "Model.h"
#include "Window.h"

Model::Model(i32 id, std::string path) {
   obj = Window::Instance()->getEngine()->createObject(path, true);
   std::cout << "Se ha cargado un edificio " << path << std::endl;
}

Model::Model(SceneNode *parent, i32 id, std::string path) {
	//ToDo
   obj = Window::Instance()->getEngine()->createObject(path, true);
   std::cout << "Se ha cargado un edificio " << path << std::endl;
}

Model::~Model() {
    meshNode -> getParent() -> removeChild(meshNode);
}

void Model::setID(i32 id) {
    
}

void Model::setName(const char *name) {
   
}

void Model::setPosition(Vector3<f32> pos) {
    obj->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

void Model::setScale(Vector3<f32> s) {
    obj->setScale(glm::vec3(s.x, s.y, s.z));
}

void Model::rotate(f32 x, f32 y){
    double param = atan(y / x) * 180 / PI;
    
}

void Model::setActive(bool a) {
    
}

void Model::setMaterial(Material *m){
    
}

Vector3<f32> Model::getPosition() {
    return Vector3<f32>(obj->getPosition().x, obj->getPosition().y, obj->getPosition().z);
}

i32 Model::getID() {
    
}

/*scene::IMeshSceneNode *Model::getModel() {
	return meshNode;
}*/