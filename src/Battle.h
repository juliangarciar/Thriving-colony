#ifndef BATTLE_H
#define BATTLE_H

#include "Unit.h"
#include <vector>
#include "GraphicEngine/Vector2.h"

class Battle {
    
    public:
        Battle(float, float);
        virtual ~Battle();

        //Getters
        std::vector<Unit*> getHumanTroops();
        std::vector<Unit*> getIaTroops();

        /////////
        void update();
        void fetchUnits();
        void determinateWinningSide();
        bool determineWithinRange(Vector3<float>*);

    private:
        //VECTOR??
        std::vector<Unit*> *humanTroops;
        std::vector<Unit*> *iaTroops;

        //VECTOR3??
        Vector2<float> *position;
};

#endif