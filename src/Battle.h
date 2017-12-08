#ifndef BATTLE_H
#define BATTLE_H

#include "Unit.h"

class Battle {
    
    public:
        Battle();
        virtual ~Battle();

        //Getters
        Unit **getHumanTroops();
        Unit **getIaTroops();

        /////////
        void determinateWinnerSide();

    private:
        Unit **humanTroops;
        Unit **iaTroops;
};

#endif