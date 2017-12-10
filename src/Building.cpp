#include "Building.h"

Building::Building(int hitPoints, Vector3<float>* pos, Enumeration::BuildingType typePnt) : Entity(hitPoints, pos) {
    type = typePnt;
}

Building::~Building() {

}
