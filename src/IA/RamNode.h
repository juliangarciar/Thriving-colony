#ifndef RAML_NODE_H
#define RAM_NODE_H

#include "Node.h"

class RamNode : public Node {

    public:
        RamNode(Node *);
        virtual ~RamNode();

    private:
        virtual void question();
};

#endif