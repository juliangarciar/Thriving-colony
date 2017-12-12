#ifndef UNIT_NODE_H
#define UNIT_NODE_H

#include "Node.h"

class UnitNode : public Node {

    public:
        UnitNode(Node *);
        virtual ~UnitNode();

        virtual void question();
        
    private:
};

#endif