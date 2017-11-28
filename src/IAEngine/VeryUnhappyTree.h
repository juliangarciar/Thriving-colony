#ifndef VERYUNHAPPY_TREE_H
#define VERYUNHAPPY_TREE_H

#include "BehaviourTree.h"
#include "Node.h"

class VeryUnhappyTree : public BehaviourTree, public Node {
    
    public:
        VeryUnhappyTree(Node*);
        virtual ~VeryUnhappyTree();

        virtual void question();

        virtual bool readyToAttack();

    private:      
};

#endif