#ifndef IA_H
#define IA_H

#include "Player.h"
#include "IAEngine/BehaviourTree.h"

class IA : public Player {
    
    public:
        IA();
        virtual ~IA();
        static IA* getInstance();

        BehaviourTree* getTree();

        Vector3<float>* determinatePositionBuilding();
        virtual void update();
    private:
        
        static IA* instance;
        BehaviourTree* tree;
};

#endif