#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
    
    public:
        Human();
        virtual ~Human();
        static Human* getInstance();

        void init();
        void cleanUp();

        static void deployTroops();
        static void retractTroops();
        static void closeDoors();
        static void openDoors();

        virtual void update();

        bool getUnderAttack();
        bool getDeployedTroops();
        bool getClosedDoors();
        /*
        void receiveMetal();
        void receiveCrystal();
        void receiveCitizens();
        */
    private:
        static Human* instance;
        static bool deployedTroops;
        static bool closedDoors;
};

#endif
