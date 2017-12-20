#include "Model.h"
#include "Window.h"

using namespace irr;

Model::Model(int id) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(id);

    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent, int id) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(id);

    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }

    parent->getSceneNode()->addChild(cubeNode);
}

Model::~Model() {
    delete selector;
    delete cubeNode;
}

void Model::setID(int id){
    cubeNode->setID(id);
}

void Model::setName(const wchar_t *name){
    cubeNode->setName(core::stringw(name).c_str());
}

scene::IMeshSceneNode *Model::getModel(){
	return cubeNode;
}