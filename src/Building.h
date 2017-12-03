#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Enumeration.h"

class Building : public Entity {
    
    public:
        Building(int);
        virtual ~Building();

    private:
        BuildingType type;
        
};

#endif