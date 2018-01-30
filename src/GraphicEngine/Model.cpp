#include "Model.h"
#include "Window.h"

using namespace irr;

Model::Model(int id, const wchar_t *path) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(path));
    meshNode -> setID(id);
    
    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent, int id, const wchar_t *path) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(path));
    meshNode -> setID(id);

    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }

    parent -> getSceneNode() -> addChild(meshNode);
}

Model::~Model() {
    meshNode -> remove();
    //selector -> drop();
}

void Model::setID(int id) {
    meshNode -> setID(id);
}

void Model::setName(const wchar_t *name) {
    meshNode -> setName(core::stringw(name).c_str());
}

void Model::setPosition(Vector3<float> pos) {
    meshNode -> setPosition(pos.getVectorF());
}

void Model::setActive(bool a) {
    meshNode -> setVisible(a);
}

void Model::setMaterial(Material *m){
    meshNode->getMaterial(0) = *m->getMaterial();
    //meshNode -> setMaterialFlag(video::EMF_LIGHTING, false);
}

Vector3<float> Model::getPosition() {
    return Vector3<float>(meshNode -> getPosition());
}

int Model::getID() {
    return meshNode -> getID();
}

scene::IMeshSceneNode *Model::getModel() {
	return meshNode;
}