#include "TNode.h"

TNode::TNode(){
    entity = nullptr;
    parent = nullptr;
}

TNode::TNode(TEntity *t){
    entity = t;
    parent = nullptr;
}

TNode::TNode(TEntity *t, TNode *p){
    entity = t;
    parent = p;
    parent->addChild(this);
}

TNode::~TNode(){
    if (entity != nullptr) delete entity;
    if (parent != nullptr) parent->removeChild(this);
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
    if (entity != nullptr) entity->beginDraw();
    for (int i=0; i<children.size(); i++){
        children[i] -> draw();
    }
    if (entity != nullptr) entity->endDraw();
}

void TNode::setEntity(TEntity *e){
    if (e != nullptr) entity = e;
}

void TNode::removeEntity(){
    if (entity != nullptr) delete entity;
}

TEntity *TNode::getEntity(){
    return entity;
}

TNode *TNode::getParent(){
    return parent;
}