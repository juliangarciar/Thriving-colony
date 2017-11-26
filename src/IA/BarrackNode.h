#ifndef BARRACK_NODE_H
#define BARRACK_NODE_H

#include "Node.h"

class BarrackNode : public Node {

    public:
        BarrackNode(Node *);
        ~BarrackNode();

    private:
        virtual void question();
};

#endif