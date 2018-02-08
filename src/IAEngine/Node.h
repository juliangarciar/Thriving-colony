#ifndef NODE_H
#define NODE_H

#include "BehaviourTree.h"
#include <Types.h>

class Node {
    
    public:
        Node();
        virtual ~Node();

        virtual void question();
        
    protected:
        Node *father;
        Node **children;

    private:
};

#endif