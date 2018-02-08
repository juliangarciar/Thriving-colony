#ifndef MELEE_FOOTMEN_NODE_H
#define MELEE_FOOTMEN_NODE_H

#include "Node.h"
#include <Types.h>

class MeleeFootmenNode : public Node {

    public:
        MeleeFootmenNode(Node *);
        virtual ~MeleeFootmenNode();

        virtual void question();
        
    private:
};

#endif