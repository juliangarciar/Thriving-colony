#ifndef MOUNTED_RANGE_NODE_H
#define MOUNTED_RANGE_NODE_H

#include "Node.h"
#include <Types.h>

class MountedRangeNode : public Node {

    public:
        MountedRangeNode(Node *);
        virtual ~MountedRangeNode();

        virtual void question();
        
    private:
};

#endif