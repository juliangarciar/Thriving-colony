#ifndef DEFEND_NODE_H
#define DEFEND_NODE_H

#include "Node.h"
#include <Types.h>

class DefendNode : public Node {

    public:
        DefendNode(Node*);
        virtual ~DefendNode();

        virtual void question();
        
    private:
};

#endif