#ifndef TOWER_NODE_H
#define TOWER_NODE_H

#include "Node.h"
#include <Types.h>

class TowerNode : public Node {

    public:
        TowerNode(Node *);
        virtual ~TowerNode();

        virtual void question();
        
    private:
};

#endif