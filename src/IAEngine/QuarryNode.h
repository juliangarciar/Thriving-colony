#ifndef QUARRY_NODE_H
#define QUARRY_NODE_H

#include "Node.h"

class QuarryNode : public Node {

    public:
        QuarryNode(Node *);
        virtual ~QuarryNode();

        virtual void question();
        
    private:
};

#endif