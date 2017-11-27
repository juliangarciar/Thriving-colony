#ifndef WALL_ATTACK_NODE_H
#define WALL_ATTACK_NODE_H

#include "Node.h"

class WallAttackNode : public Node {

    public:
        WallAttackNode(Node *);
        virtual ~WallAttackNode();

    private:
        virtual void question();
};

#endif