#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
    
    public:
        Human();
        virtual ~Human();
        static Human* getInstance();

        void init();
        void update();
        void cleanUp();

        //ToDo: Por que estático?
        static void deployTroops();
        static void retractTroops();
        static void closeDoors();
        static void openDoors();

        bool getUnderAttack();
        bool getDeployedTroops();
        bool getClosedDoors();
    private:

        static Human* instance;
        static bool deployedTroops;
        static bool closedDoors;
};

#endif
