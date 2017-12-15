#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include "Enumeration.h"
#include "GraphicEngine/Vector3.h"

class Building : public Entity {
    
    public:
        //Enum: Barn,Barrack,Hospital,House,MainBuilding,Market,Quarry,Siderurgy,School,Tower,Wall,Workshop
        //teamData sepecifies the building team and vectorData the position
        Building(Enumeration::BuildingType buildingData, Vector3<float> *vectorData, bool teamData, Model *modelData, Box3D<float> *boxData); //ToDo: el modelo y la hitbox se crean en el constructor
        virtual ~Building();

    private:
        Enumeration::BuildingType type;
        
};

#endif