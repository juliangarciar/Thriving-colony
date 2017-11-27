#ifndef BUILDING_ATTACK_NODE_H
#define BUILDING_ATTACK_NODE_H

#include "Node.h"

class BuildingAttackNode : public Node {

    public:
        BuildingAttackNode(Node *);
        virtual ~BuildingAttackNode();

    private:
        virtual void question();
};

#endif