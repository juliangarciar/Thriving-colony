#include "Node.h"
#include "../IA.h"

Node::Node() {
    tree = IA::getInstance() -> getTree();
}

Node::~Node() {
    delete tree;
}

void Node::question(){}
