#include "OBDAnimation.h"

OBDAnimation::OBDAnimation(OBDSceneNode* parent) : OBDEntity(parent){
    //animationNode = new TNode(new TMesh(), scaleNode);
    //ToDo: hacer animaciones

    parent->addChild(this);
}

OBDAnimation::~OBDAnimation() {

}