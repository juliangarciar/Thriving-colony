#include "Composite.h"

Composite::Composite(std::vector<Behaviour*> newChildren) : Behaviour(){
    children = newChildren;
}

Composite::~Composite() {
    for (i32 i = 0; i < children.size(); i++) {
        delete children.at(i);
    }
    children.clear();
}