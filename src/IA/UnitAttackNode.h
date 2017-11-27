#ifndef UNIT_ATTACK_NODE_H
#define UNIT_ATTACK_NODE_H

#include "Node.h"

class UnitAttackNode : public Node {

    public:
        UnitAttackNode(Node *);
        virtual ~UnitAttackNode();

    private:
        virtual void question();
};

#endif