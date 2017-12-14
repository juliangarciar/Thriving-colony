#ifndef WALL_NODE_H
#define WALL_NODE_H

#include "Node.h"

class WallNode : public Node {

    public:
        WallNode(Node *);
        virtual ~WallNode();

        virtual void question();
        
    private:
};

#endif