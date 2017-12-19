#include "Node.h"
#include "../IA.h"

Node::Node() {
    tree = IA::getInstance() -> getTree();
}

Node::~Node() {
    delete tree;
}

void Node::question(){}

bool Node::isSolvent(int metalCost, int crystalCost) {
    bool canPayMetal = IA::getInstance() -> getMetalAmount() >= metalCost;
    bool canPayCrystal = Ia::getInstance() -> getCrystalAmount() >= crystalCost;
    
    return (canPayMetal && canPayCrystal);
}