#ifndef CATAPULT_NODE_H
#define CATAPULT_NODE_H

#include "Node.h"
#include <Types.h>

class CatapultNode : public Node {

    public:
        CatapultNode(Node *);
        virtual ~CatapultNode();

        virtual void question();
        
    private:
};

#endif