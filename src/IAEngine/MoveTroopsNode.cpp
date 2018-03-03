#include "MoveTroopsNode.h"
#include <IA.h>
#include <Game.h>

MoveTroopsNode::MoveTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

MoveTroopsNode::~MoveTroopsNode(){
    delete father;
}

void MoveTroopsNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::Attacking);
    //ToDo: Fijar centro de mando como objetivo
    //Game::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::DeployTroopsIA);
    IA::Instance() -> getUnitManager() -> deployAllTroops(Vector3<f32>(Enumeration::HumanCityHall::human_x, Map::Instance() -> getTerrain() -> getY(Enumeration::HumanCityHall::human_x, Enumeration::HumanCityHall::human_z), Enumeration::HumanCityHall::human_z));
}