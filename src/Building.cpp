#include "Building.h"

Building::Building(int hitPoints, Vector3<float>* pos, Enumeration::BuildingType typePnt, bool _team) : Entity(hitPoints, pos, _team) {
    type = typePnt;
}

Building::~Building() {
    
}
