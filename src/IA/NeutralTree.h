#ifndef NEUTRAL_TREE_H
#define NEUTRAL_TREE_H

#include "BehaviourTree.h"

class NeutralTree : public BehaviourTree {
    
    public:
        NeutralTree();
        ~NeutralTree();

        virtual void developCity();

        virtual bool readyToAttack();

    private:
};

#endif