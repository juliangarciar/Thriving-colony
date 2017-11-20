#ifndef UNHAPPY_TREE_H
#define UNHAPPY_TREE_H

#include "BehaviourTree.h"

class UnhappyTree : public BehaviourTree {

    public:
        UnhappyTree(IA*);
        ~UnhappyTree();

        virtual void developCity();

        virtual bool readyToAttack();
        
    private:
};

#endif