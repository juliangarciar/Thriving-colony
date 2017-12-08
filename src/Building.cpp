#include "Building.h"

Building::Building(int hpPnt, Enumeration::BuildingType typePnt) : Entity(hpPnt) {
    type = typePnt;
}

Building::~Building() {

}
