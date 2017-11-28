#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "Node.h"

class RootNode : public Node {

    public:
        RootNode(Node*);
        virtual ~RootNode();

    private:
        virtual void question();
};

#endif