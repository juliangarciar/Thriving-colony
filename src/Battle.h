#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include "GraphicEngine/Vector2.h"
#include "Enumeration.h"
//#include "Entity.h"
#include "Unit.h"
#include "Building.h"

class Battle {
    
    public:
        Battle(float, float);
        virtual ~Battle();

        //Getters
        std::vector<Unit*>* getHumanTroops();
        std::vector<Unit*>* getIaTroops();

        /////////
        void update();
        void fetchUnits();
        void fetchBuildings();

        void determinateWinningSide();
        bool determineWithinRange(Vector3<float>*);
        Entity* getClosestTarget(Vector3<float>*, Enumeration::Team);

    private:
        //VECTOR
        std::vector<Unit*> *humanTroops;
        std::vector<Unit*> *iaTroops;

        std::vector<Building*> *humanBuildings;
        std::vector<Building*> *iaBuildings;

        //VECTOR2
        Vector2<float> *position;

        float unitFetchTimer;
        float buildingFetchTimer;
};

#endif