#ifndef WALL_NODE_H
#define WALL_NODE_H

#include "Node.h"

class WallNode : public Node {

    public:
        WallNode(Node *);
        ~WallNode();

    private:
        virtual void question();
};

#endif