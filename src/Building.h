#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Enumeration.h"
#include "GraphicEngine/Vector3.h"

class Building : public Entity {
    
    public:
        Building(int, Vector3<float>*, Enumeration::BuildingType, bool);
        virtual ~Building();

    private:
        Enumeration::BuildingType type;
        
};

#endif