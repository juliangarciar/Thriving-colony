#ifndef TNODE_H
#define TNODE_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TEntity.h"

class TNode {
    public:
        TNode(TNode*);
        ~TNode();

        void addChild(TNode*);
        void removeChild(TNode*);

        void draw();

        void setEntity(TEntity*);

        TEntity *getEntity();
        TNode *getParent();
    private:
        TEntity *entity;
        TNode *parent;
        std::vector<TNode*> children;
};

#endif