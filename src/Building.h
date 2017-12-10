#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Enumeration.h"
#include "GraphicEngine/Vector3.h"
#include "Player.h"

class Building : public Entity {
    
    public:
        Building(int hpPnt, Vector3<float>*, Player*, Enumeration::BuildingType);
        virtual ~Building();

    private:
        Enumeration::BuildingType type;
        
};

#endif