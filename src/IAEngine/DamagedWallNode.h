#ifndef DAMAGED_WALL_NODE_H
#define DAMAGED_WALL_NODE_H

#include "Node.h"

class DamagedWallNode : public Node {

    public:
        DamagedWallNode(Node *);
        virtual ~DamagedWallNode();

        virtual void question();
        
    private:
};

#endif