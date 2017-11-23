#ifndef QUARRY_NODE_H
#define QUARRY_NODE_H

#include "Node.h"

class QuarryNode : public Node {

    public:
        QuarryNode(Node *);
        ~QuarryNode();

    private:
        virtual void question();
};

#endif