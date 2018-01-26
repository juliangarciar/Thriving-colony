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

        void init();
        void cleanUp();

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

        void setChoiceIndex(int);
        std::wstring getNextChoice();
        std::wstring getChosenBehaviour();
        void initializeChoices();

        void chooseBehaviour();
    private:
        static IA* instance;
        static bool deployedTroops;
        static bool closedDoors;
        BehaviourTree* tree;
        RootNode *nodeRootIA;

        Enumeration::IABehaviour behaviour;
        std::wstring chosenBehaviour;
        int choiceIndex;

        std::vector<std::wstring> * choices;

};

#endif