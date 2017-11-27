#ifndef CLOSE_UNIT_NODE_H
#define CLOSE_UNIT_NODE_H

#include "Node.h"

class CloseUnitNode : public Node {

    public:
        CloseUnitNode(Node *);
        virtual ~CloseUnitNode();

    private:
        virtual void question();
};

#endif