#ifndef DAMAGED_WALL_NODE_H
#define DAMAGED_WALL_NODE_H

#include "Node.h"

class DamagedWallNode : public Node {

    public:
        DamagedWallNode(Node *);
        ~DamagedWallNode();

    private:
        virtual void question();
};

#endif