#ifndef MELEE_NODE_H
#define MELEE_NODE_H

#include "Node.h"

class MeleeNode : public Node {

    public:
        MeleeNode(Node *);
        virtual ~MeleeNode();

        virtual void question();
        
    private:
};

#endif