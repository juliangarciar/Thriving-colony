#include "Building.h"
#include "GraphicEngine/Vector3.h"
#include "Player.h"

Building::Building(int hitPoints, Vector3<float>* pos, Player* _team, Enumeration::BuildingType typePnt) : Entity(hitPoints, pos, _team) {
    type = typePnt;
}

Building::~Building() {

}
