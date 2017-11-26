#ifndef MELEE_FOOTMEN_NODE_H
#define MELEE_FOOTMEN_NODE_H

#include "Node.h"

class MeleeFootmenNode : public Node {

    public:
        MeleeFootmenNode(Node *);
        ~MeleeFootmenNode();

    private:
        virtual void question();
};

#endif