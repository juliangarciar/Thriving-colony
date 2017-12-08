#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Enumeration.h"

class Building : public Entity {
    
    public:
        Building(int hpPnt, Enumeration::BuildingType);
        virtual ~Building();

    private:
        Enumeration::BuildingType type;
        
};

#endif