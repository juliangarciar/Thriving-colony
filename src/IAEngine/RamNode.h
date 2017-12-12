#ifndef RAM_NODE_H
#define RAM_NODE_H

#include "Node.h"

class RamNode : public Node {

    public:
        RamNode(Node *);
        virtual ~RamNode();

        virtual void question();
        
    private:
};

#endif