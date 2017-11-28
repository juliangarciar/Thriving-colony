#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

class Building : public Entity {
    
    public:
        Building(int);
        virtual ~Building();

        enum BuildingType {
            MainBuilding,
            House,
            Quarry,
            Siderurgy,
            Market,
            Hospital,
            School,
            Workshop,
            Barrack,
            Barn,
            Tower,
            Wall
        };

    private:
        BuildingType type;
        
};

#endif