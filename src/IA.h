#ifndef IA_H
#define IA_H

#include "Player.h"
#include "IAEngine/BehaviourTree.h"
#include "IAEngine/RootNode.h"

class IA : public Player {
    
    public:
        IA();
        virtual ~IA();
        static IA* getInstance();

        static void deployTroops();
        static void retractTroops();
        static void closeDoors();
        static void openDoors();

        BehaviourTree* getTree();

        Vector3<float> determinatePositionBuilding();
        virtual void update();

        bool getUnderAttack();
        bool getDeployedTroops();
        bool getClosedDoors();

    private:
        static IA* instance;
        static bool deployedTroops;
        static bool closedDoors;
        BehaviourTree* tree;
        RootNode *nodeRootIA;

};

#endif