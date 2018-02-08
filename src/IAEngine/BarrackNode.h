#ifndef BARRACK_NODE_H
#define BARRACK_NODE_H

#include "Node.h"
#include <Types.h>

class BarrackNode : public Node {

    public:
        BarrackNode(Node *);
        virtual ~BarrackNode();

        virtual void question();
        
    private:
};

#endif