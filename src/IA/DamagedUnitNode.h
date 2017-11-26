#ifndef DAMAGED_UNIT_NODE_H
#define DAMAGED_UNIT_NODE_H

#include "Node.h"

class DamagedUnitNode : public Node {

    public:
        DamagedUnitNode(Node *);
        ~DamagedUnitNode();

    private:
        virtual void question();
};

#endif