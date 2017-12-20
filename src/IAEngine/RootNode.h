#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "Node.h"

class RootNode : public Node {

    public:
        RootNode();
        virtual ~RootNode();

        virtual void question();

    private:
};

#endif