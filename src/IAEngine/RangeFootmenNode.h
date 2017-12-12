#ifndef RANGE_FOOTMEN_NODE_H
#define RANGE_FOOTMEN_NODE_H

#include "Node.h"

class RangeFootmenNode : public Node {

    public:
        RangeFootmenNode(Node *);
        virtual ~RangeFootmenNode();

        virtual void question();
        
    private:
};

#endif