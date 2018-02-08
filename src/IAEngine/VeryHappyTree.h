#ifndef VERYHAPPY_TREE_H
#define VERYHAPPY_TREE_H

#include "Node.h"
#include <Types.h>

class VeryHappyTree : public Node {
    
    public:
        VeryHappyTree(Node*);
        virtual ~VeryHappyTree();

        virtual void question();

        virtual bool readyToAttack();
    
    private:
};

#endif