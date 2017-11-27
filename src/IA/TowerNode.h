#ifndef TOWER_NODE_H
#define TOWER_NODE_H

#include "Node.h"

class TowerNode : public Node {

    public:
        TowerNode(Node *);
        virtual ~TowerNode();

    private:
        virtual void question();
};

#endif