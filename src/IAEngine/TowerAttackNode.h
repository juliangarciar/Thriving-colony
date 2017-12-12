#ifndef TOWER_ATTACK_NODE_H
#define TOWER_ATTACK_NODE_H

#include "Node.h"

class TowerAttackNode : public Node {

    public:
        TowerAttackNode(Node *);
        ~TowerAttackNode();

        virtual void question();
        
    private:
};

#endif