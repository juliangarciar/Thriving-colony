#ifndef DEFEND_NODE_H
#define DEFEND_NODE_H

#include "Node.h"

class DefendNode : public Node {

    public:
        DefendNode(Node*);
        virtual ~DefendNode();

    private:
        virtual void question();
};

#endif