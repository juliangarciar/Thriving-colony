#include "Composite.h"

Composite::Composite(std::vector<Behaviour*> newChildren) : Behaviour(){
    if (newChildren != NULL) {
        children = newChildren;
    }
}

Composite::~Composite() {

}