#ifndef NODE_H
#define NODE_H

#include "BehaviourTree.h"

class Node {
    
    public:
        Node();
        ~Node();

        virtual void question();

    protected:
        Node *father;
        Node **children;

        BehaviourTree* tree;
    private:
};

#endif