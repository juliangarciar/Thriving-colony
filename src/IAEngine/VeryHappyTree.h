#ifndef VERYHAPPY_TREE_H
#define VERYHAPPY_TREE_H

#include "Node.h"
#include "BehaviourTree.h"

class VeryHappyTree : public BehaviourTree, public Node {
    
    public:
        VeryHappyTree(Node*);
        virtual ~VeryHappyTree();

        virtual void question();

        virtual bool readyToAttack();
    
    private:
};

#endif