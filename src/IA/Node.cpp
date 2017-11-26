#include "Node.h"

Node::Node() {
    tree = IA::getInstance() -> getTree();
}

Node::~Node() {
    
}

void Node::question(){}