#ifndef UNHAPPY_TREE_H
#define UNHAPPY_TREE_H

#include "BehaviourTree.h"

class UnhappyTree : public BehaviourTree {

    public:
        UnhappyTree();
        ~UnhappyTree();

        virtual void developCity();

        virtual bool readyToAttack();
        
    private:
};

#endif