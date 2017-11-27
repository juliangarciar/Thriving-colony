#ifndef ATTACKING_UNIT_NODE_H
#define ATTACKING_UNIT_NODE_H

#include "Node.h"

class AttackingUnitNode : public Node {

    public:
        AttackingUnitNode(Node *);
        virtual ~AttackingUnitNode();

    private:
        virtual void question();
};

#endif