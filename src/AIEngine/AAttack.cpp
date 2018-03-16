#include "AAttack.h"
#include "../IA.h"
#include "../Map.h"

AAttack::AAttack() : Action() {

}

AAttack::~AAttack() {

}

Enumeration::BehaviourState AAttack::Update() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::Attacking);
    IA::Instance() -> getUnitManager() -> deployAllTroops(Vector3<f32>(Enumeration::HumanCityHall::human_x, Map::Instance() -> getTerrain() -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z));
    return Enumeration::BehaviourState::Success;
}