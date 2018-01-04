#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"


class Building : public Entity {
    
    public:
        //Enum: Barn,Barrack,Hospital,House,MainBuilding,Market,Quarry,Siderurgy,School,Tower,Wall,Workshop
        //teamData sepecifies the building team and vectorData the position
        Building(int id, SceneNode *parent, Enumeration::BuildingType buildingData, Vector3<float> vectorData, Enumeration::Team teamData);
        virtual ~Building();

        virtual void taxPlayer(Enumeration::Team);
        void specialTax(Enumeration::Team);
        irr::video::SColor getColor();
        int getType();
        void update();
    private:
        int type;

        int stepsToBuild;
        int currentStep;

        irr::video::SColor baseColor;
        irr::video::SColor currentColor;
};

#endif