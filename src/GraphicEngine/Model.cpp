#include "Model.h"
#include "Window.h"

using namespace irr;

Model::Model(i32 id, const wchar_t *path) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(path));
    meshNode -> setID(id);
    
    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent, i32 id, const wchar_t *path) {
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

void Model::setID(i32 id) {
    meshNode -> setID(id);
}

void Model::setName(const wchar_t *name) {
    meshNode -> setName(core::stringw(name).c_str());
}

void Model::setPosition(Vector3<f32> pos) {
    meshNode -> setPosition(pos.getVectorF());
}

void Model::setScale(Vector3<f32> s) {
    meshNode -> setScale(s.getVectorF()); 
}

void Model::setActive(bool a) {
    meshNode -> setVisible(a);
}

void Model::setMaterial(Material *m){
    meshNode->getMaterial(0) = *m->getMaterial();
}

Vector3<f32> Model::getPosition() {
    return Vector3<f32>(meshNode -> getPosition());
}
Box3D<f32> Model::getBoundingBox() {
    meshNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    core::aabbox3df box = meshNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    meshNode->getMesh()->setBoundingBox(box);
    
    return Box3D<f32>(meshNode -> getTransformedBoundingBox());
}

i32 Model::getID() {
    return meshNode -> getID();
}

scene::IMeshSceneNode *Model::getModel() {
	return meshNode;
}