#ifndef DAMAGED_UNIT_NODE_H
#define DAMAGED_UNIT_NODE_H

#include "Node.h"

class DamagedUnitNode : public Node {

    public:
        DamagedUnitNode(Node *);
        virtual ~DamagedUnitNode();

        virtual void question();
        
    private:
};

#endif