#ifndef HAPPY_TREE_H
#define HAPPY_TREE_H

#include "BehaviourTree.h"

class HappyTree : public BehaviourTree {
    
    public: 
        HappyTree();
        virtual ~HappyTree();

        virtual void developCity();

        virtual bool readyToAttack();

    private:
};

#endif