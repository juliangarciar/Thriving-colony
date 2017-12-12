#include "Model.h"
#include "Window.h"

using namespace irr;

Model::Model() {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(std::rand());

    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }
}

Model::Model(SceneNode *parent) {
    cubeNode = Window::Instance()->getSceneManager()->addCubeSceneNode(100);
    cubeNode->setID(std::rand());

    selector = Window::Instance()->getSceneManager()->createTriangleSelectorFromBoundingBox(cubeNode);
    if (selector) {
        cubeNode->setTriangleSelector(selector);
        selector->drop(); // We're done with this selector, so drop it now.
    }

    parent->getSceneNode()->addChild(cubeNode);

    /*scene::ISceneNode *n;
	if ((n = w->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, point, triangle, 0, node))){
		std::cout << n->getID() << std::endl;
		return SceneNode(n);
	}

	return SceneNode();*/
} 

Model::~Model() {
    delete selector;
    delete cubeNode;
}

scene::IMeshSceneNode *Model::getModel(){
	return cubeNode;
}