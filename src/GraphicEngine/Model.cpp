#include "Model.h"
#include "Window.h"
#include <cmath>
#include "../Map.h"

using namespace irr;
#define PI 3.14159265

Model::Model(i32 id, std::string path) {
    const char* c = path.c_str();
    std::wstringstream o;
    o << c;

    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(o.str().c_str()));
    if (!meshNode) {
        std::cout << "ERROR: no se puede cargar el modelo: " << c << std::endl;
        exit(0);
    }
    meshNode -> setID(id);
    
    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent, i32 id, std::string path) {
    const char* c = path.c_str();
    std::wstringstream o;
    o << c;

    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(o.str().c_str()));
    if (!meshNode) {
        std::cout << "ERROR: no se puede cargar el modelo: " << path << std::endl;
        exit(0);
    }
    meshNode -> setID(id);

    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }
    
    parent -> getSceneNode() -> addChild(meshNode);
}

Model::~Model() {
    meshNode -> getParent() -> removeChild(meshNode);
}

void Model::setID(i32 id) {
    meshNode -> setID(id);
}

void Model::setName(const char *name) {
    meshNode -> setName(core::stringw(name).c_str());
}

void Model::setPosition(Vector3<f32> pos) {
    meshNode -> setPosition(core::vector3df(pos.x, pos.y, pos.z));
}

void Model::setScale(Vector3<f32> s) {
    meshNode -> setScale(core::vector3df(s.x, s.y, s.z)); 
}

void Model::rotate(f32 x, f32 y){
    double param = atan(y / x) * 180 / PI;
    //if(x < 0 && y < 0)
    //    param += 180;
    //else if(x < 0)
    //    param += 90;
    //else if(y < 0)
    //    param += 270;
    meshNode->setRotation(core::vector3df(0, param, 0));
}
void Model::setActive(bool a) {
    meshNode -> setVisible(a);
}

void Model::setMaterial(Material *m){
    meshNode->getMaterial(0) = *m->getMaterial();
}

void Model::setMaterialColor(Color c){
    meshNode->getMaterial(0).DiffuseColor = video::SColor(c.a, c.r, c.g, c.b);
}

Vector3<f32> Model::getPosition() {
    return Vector3<f32>(meshNode -> getPosition().X, meshNode -> getPosition().Y, meshNode -> getPosition().Z);
}

i32 Model::getID() {
    return meshNode -> getID();
}

scene::IMeshSceneNode *Model::getModel() {
	return meshNode;
}