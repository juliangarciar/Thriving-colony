#ifndef MOUNTED_MELEE_NODE_H
#define MOUNTED_MELEE_NODE_H

#include "Node.h"

class MountedMeleeNode : public Node {

    public:
        MountedMeleeNode(Node *);
        virtual ~MountedMeleeNode();

    private:
        virtual void question();
};

#endif