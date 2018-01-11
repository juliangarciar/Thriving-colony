#include "Model.h"
#include "Window.h"

using namespace irr;

Model::Model(int id) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(id);

    cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
    
    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent, int id) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(id);

    cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);

    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }

    parent->getSceneNode()->addChild(cubeNode);
}

Model::~Model() {
    cubeNode->remove();

    delete selector;
    delete cubeNode;
}

void Model::setID(int id){
    cubeNode->setID(id);
}

void Model::setName(const wchar_t *name){
    cubeNode->setName(core::stringw(name).c_str());
}

void Model::setPosition(Vector3<float> pos){
    cubeNode->setPosition(pos.getVectorF());
}

void Model::setActive(bool a){
    cubeNode->setVisible(a);
}

Vector3<float> Model::getPosition(){
    return Vector3<float>(cubeNode->getPosition());
}

int Model::getID(){
    return cubeNode->getID();
}

scene::IMeshSceneNode *Model::getModel(){
	return cubeNode;
}