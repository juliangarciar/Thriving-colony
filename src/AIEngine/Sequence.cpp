#include "Sequence.h"

Sequence::Sequence(std::vector<Behaviour*> newChildren) : Composite(newChildren) {
    
}

Sequence::~Sequence() {

}

Enumeration::BehaviourState Sequence::Update() {
    i32 i = 0;
    while(i < children.size() && children.at(i) -> Update() == Enumeration::BehaviourState::Success) {
        i++;
    }
    if (i ==  0) {
        return Enumeration::BehaviourState::Failure;
    } else {
        return Enumeration::BehaviourState::Success;
    }
}