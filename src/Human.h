#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <Types.h>

class Human : public Player {
    
    public:
        Human();
        virtual ~Human();
        static Human* Instance();

        void init();
        void update();
        void cleanUp();

        //ToDo: Por que estático?
        static void retractTroops();

        bool getUnderAttack();
        bool getDeployedTroops();
        bool getClosedDoors();
    private:
        static Human* instance;

        i32 updateTimer;

        //ToDo: Por que estático?
        static bool deployedTroops;
        static bool closedDoors;
};

#endif
