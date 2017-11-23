#ifndef BUILDING_NODE_H
#define BUILDING_NODE_H

#include "Node.h"

class BuildingNode : public Node {

    public:
        BuildingNode(Node *);
        ~BuildingNode();

    private:
        virtual void question();
};

#endif