#include "Model.h"
#include "Window.h"

Model::Model() {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
}

Model::Model(SceneNode *parent) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    parent->getSceneNode()->addChild(cubeNode);
}

Model::~Model() {

}

scene::IMeshSceneNode *Model::getModel(){
	return cubeNode;
}