#ifndef CREATURE_NODE_H
#define CREATURE_NODE_H

#include "Node.h"
#include <Types.h>

class CreatureNode : public Node {

    public:
        CreatureNode(Node *);
        virtual ~CreatureNode();

        virtual void question();
        
    private:
};

#endif