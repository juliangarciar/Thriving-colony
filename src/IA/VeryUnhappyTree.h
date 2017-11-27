#ifndef VERYUNHAPPY_TREE_H
#define VERYUNHAPPY_TREE_H

#include "BehaviourTree.h"

class VeryUnhappyTree : public BehaviourTree {
    
    public:
        VeryUnhappyTree();
        virtual ~VeryUnhappyTree();

        virtual void developCity();

        virtual bool readyToAttack();

    private:      
};

#endif