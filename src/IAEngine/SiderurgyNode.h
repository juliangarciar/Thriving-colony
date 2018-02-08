#ifndef SIDERURGY_NODE_H
#define SIDERURGY_NODE_H

#include "Node.h"
#include <Types.h>

class SiderurgyNode : public Node {

    public:
        SiderurgyNode(Node *);
        virtual ~SiderurgyNode();

        virtual void question();
        
    private:
};

#endif