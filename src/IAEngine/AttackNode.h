#ifndef ATTACK_NODE_H
#define ATTACK_NODE_H

#include "Node.h"

class AttackNode : public Node {

    public:
        AttackNode(Node*);
        virtual ~AttackNode();

        virtual void question();
        
    private:
};

#endif