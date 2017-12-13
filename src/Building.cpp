#include "Building.h"

Building::Building(int hitPoints, Vector3<float>* pos, Enumeration::BuildingType typePnt, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Entity() {
    type = typePnt;
}

Building::~Building() {
    
}
