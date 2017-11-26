#ifndef MAIN_BUILDING_ATTACK_NODE_H
#define MAIN_BUILDING_ATTACK_NODE_H

#include "Node.h"

class MainBuildingAttackNode : public Node {

    public:
        MainBuildingAttackNode(Node *);
        ~MainBuildingAttackNode();

    private:
        virtual void question();
};

#endif