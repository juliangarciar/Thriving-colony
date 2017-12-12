#ifndef RANGE_NODE_H
#define RANGE_NODE_H

#include "Node.h"

class RangeNode : public Node {

    public:
        RangeNode(Node *);
        virtual ~RangeNode();

        virtual void question();
        
    private:
};

#endif