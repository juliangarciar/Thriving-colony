#ifndef BATTLE_H
#define BATTLE_H

#include "Unit.h"
#include <vector>

class Battle {
    
    public:
        Battle(int, int);
        virtual ~Battle();

        //Getters
        std::vector<Unit*> getHumanTroops();
        std::vector<Unit*> getIaTroops();

        /////////
        void update();
        void fetchUnits();
        void determinateWinningSide();
        bool determineWithingRange(Vector3);

    private:
        //VECTOR??
        std::vector<Unit*> *humanTroops;
        std::vector<Unit*> *iaTroops;

        //VECTOR3??
        Vector3 position;
};

#endif