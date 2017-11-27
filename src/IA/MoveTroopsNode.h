#ifndef MOVE_TROOPS_NODE_H
#define MOVE_TROOPS_NODE_H

#include "Node.h"

class MoveTroopsNode : public Node {

    public:
        MoveTroopsNode(Node*);
        virtual ~MoveTroopsNode();

    private:
        virtual void question();
};

#endif