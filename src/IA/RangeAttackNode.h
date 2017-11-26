#ifndef RANGE_ATTACK_NODE_H
#define RANGE_ATTACK_NODE_H

#include "Node.h"

class RangeAttackNode : public Node {

    public:
        RangeAttackNode(Node *);
        ~RangeAttackNode();

    private:
        virtual void question();
};

#endif