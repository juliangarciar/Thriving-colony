#ifndef ARMY_NODE_H
#define ARMY_NODE_H

#include "Node.h"

class ArmyNode : public Node {

    public:
        ArmyNode(Node*);
        virtual ~ArmyNode();

        virtual void question();
        
    private:
};

#endif