#include "ActiveSelector.h"

ActiveSelector::ActiveSelector(std::vector<Behaviour*> newChildren) : Selector(newChildren){
    priority = NULL;
}

ActiveSelector::~ActiveSelector() {

}

Enumeration::BehaviourState ActiveSelector::Update() {
    if (priority != NULL){
        if (priority -> Update() == Enumeration::BehaviourState::Success) {
            return Enumeration::BehaviourState::Success;
        }
        return Enumeration::BehaviourState::Failure;
    } else {
        Selector::Update();
    }
}

void ActiveSelector::setPriority(Behaviour* newPriority) {
    priority = newPriority;
}