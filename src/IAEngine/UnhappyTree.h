#ifndef UNHAPPY_TREE_H
#define UNHAPPY_TREE_H

#include "BehaviourTree.h"
#include "Node.h"
#include <Types.h>

class UnhappyTree : public BehaviourTree, public Node {

    public:
        UnhappyTree(Node*);
        ~UnhappyTree();

        virtual void question();

        virtual bool readyToAttack();
        
    private:
};

#endif