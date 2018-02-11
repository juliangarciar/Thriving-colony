#include "TNode.h"

TNode::TNode(TNode *p){
    parent = p;
    entity = NULL;
}

TNode::~TNode(){
    delete entity;
    delete parent;
    for (int i = 0; i < children.size(); i++){
        delete children[i];
    }
}

void TNode::addChild(TNode *c){
    children . push_back(c);
}

void TNode::removeChild(TNode *c){
    children . erase(std::remove(children . begin(), children . end(), c), children . end());
}

void TNode::draw(){
    if (entity != NULL) entity->beginDraw();
    for (int i=0; i<children.size(); i++){
        children[i] -> draw();
    }
    if (entity != NULL) entity->endDraw();
}

void TNode::setEntity(TEntity *e){
    entity = e;
}

TEntity *TNode::getEntity(){
    return entity;
}

TNode *TNode::getParent(){
    return parent;
}