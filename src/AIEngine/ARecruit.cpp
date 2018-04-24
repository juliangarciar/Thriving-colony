#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit() : Action() {

}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update(std::string type) {
    if (type == "DefenseStandardM") {
        type = "StandardM";
    }
    IA::Instance() -> getUnitManager() -> createTroop(type);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARecruit::Update() {
    return Enumeration::BehaviourState::Failure;
}