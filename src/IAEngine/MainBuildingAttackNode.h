#ifndef MAIN_BUILDING_ATTACK_NODE_H
#define MAIN_BUILDING_ATTACK_NODE_H

#include "Node.h"

class MainBuildingAttackNode : public Node {

    public:
        MainBuildingAttackNode(Node *);
        virtual ~MainBuildingAttackNode();

        virtual void question();
        
    private:
};

#endif