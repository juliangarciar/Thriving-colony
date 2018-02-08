#ifndef MOVE_TROOPS_NODE_H
#define MOVE_TROOPS_NODE_H

#include "Node.h"
#include <Types.h>

class MoveTroopsNode : public Node {

    public:
        MoveTroopsNode(Node*);
        virtual ~MoveTroopsNode();

        virtual void question();
        
    private:
};

#endif