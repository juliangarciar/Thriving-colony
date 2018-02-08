#ifndef CLOSE_DOORS_NODE_H
#define CLOSE_DOORS_NODE_H

#include "Node.h"
#include <Types.h>

class CloseDoorsNode : public Node {

    public:
        CloseDoorsNode(Node*);
        virtual ~CloseDoorsNode();

        virtual void question();
        
    private:
};

#endif