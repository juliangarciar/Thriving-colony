#ifndef NEUTRAL_TREE_H
#define NEUTRAL_TREE_H

#include "BehaviourTree.h"
#include "Node.h"

class NeutralTree : public BehaviourTree, public Node {
    
    public:
        NeutralTree(Node *);
        ~NeutralTree();

        virtual void question();

        virtual bool readyToAttack();

    private:
};

#endif