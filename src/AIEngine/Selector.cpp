#include "Selector.h"

Selector::Selector(std::vector<Behaviour*> newChildren) : Composite(newChildren) {
    
}

Selector::~Selector() {

}

Enumeration::BehaviourState Selector::Update() {
    for (i32 i = 0; i < children.size(); i++) {
        if (children.at(i) -> Update() == Enumeration::BehaviourState::Success) {
            return Enumeration::BehaviourState::Success;
        }
    }
    return Enumeration::BehaviourState::Failure;
}