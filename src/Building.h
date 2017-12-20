#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"


class Building : public Entity {
    
    public:
        //Enum: Barn,Barrack,Hospital,House,MainBuilding,Market,Quarry,Siderurgy,School,Tower,Wall,Workshop
        //teamData sepecifies the building team and vectorData the position
<<<<<<< HEAD
        Building(Enumeration::BuildingType buildingData, Vector3<float> *vectorData, Enumeration::Team teamData);
=======
        Building(SceneNode *parent, Enumeration::BuildingType buildingData, Vector3<float> *vectorData, bool teamData);
>>>>>>> GraphicEngine
        virtual ~Building();

    private:
        Enumeration::BuildingType type;
        
};

#endif