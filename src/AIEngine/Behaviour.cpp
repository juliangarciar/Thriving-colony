#include "Behaviour.h"

Behaviour::Behaviour() {
    state = Enumeration::BehaviourState::Invalid;    
}

Behaviour::~Behaviour() {

}

Enumeration::BehaviourState Behaviour::Update() {

}

Enumeration::BehaviourState Behaviour::getState() {
    return state;
}