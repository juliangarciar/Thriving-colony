#include "Building.h"

Building::Building(int hitPoints, Vector3<float>* pos, Enumeration::BuildingType typePnt, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Entity(hitPoints, pos, _team, hitboxPnt, modelPnt) {
    type = typePnt;
}

Building::~Building() {
    
}
