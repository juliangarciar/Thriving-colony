#ifndef BARN_NODE_H
#define BARN_NODE_H

#include "Node.h"

class BarnNode : public Node {

    public:
        BarnNode(Node *);
        virtual ~BarnNode();

    private:
        virtual void question();
};

#endif