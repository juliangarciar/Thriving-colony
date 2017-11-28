#ifndef HAPPY_TREE_H
#define HAPPY_TREE_H

#include "BehaviourTree.h"
#include "Node.h"

class HappyTree : public BehaviourTree, public Node {
    
    public: 
        HappyTree(Node*);
        virtual ~HappyTree();

        virtual void question();

        virtual bool readyToAttack();

    private:
};

#endif