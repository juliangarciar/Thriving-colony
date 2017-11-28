#ifndef RESOURCE_NODE_H
#define RESOURCE_NODE_H

#include "Node.h"

class ResourceNode : public Node {

    public:
        ResourceNode(Node*);
        virtual ~ResourceNode();

    private:
        virtual void question();
};

#endif