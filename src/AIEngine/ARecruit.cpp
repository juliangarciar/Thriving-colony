#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit() : Action() {

}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update(Enumeration::UnitType type) {
    IA::Instance() -> getUnitManager() -> createTroop(type);
    return Enumeration::BehaviourState::Success;
}