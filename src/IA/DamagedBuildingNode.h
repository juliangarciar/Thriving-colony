#ifndef DAMAGED_BUILDING_NODE_H
#define DAMAGED_BUILDING_NODE_H

#include "Node.h"

class DamagedBuildingNode : public Node {

    public:
        DamagedBuildingNode(Node *);
        ~DamagedBuildingNode();

    private:
        virtual void question();
};

#endif