#ifndef SERVICE_NODE_H
#define SERVICE_NODE_H

#include "Node.h"
#include <Types.h>

class ServiceNode : public Node {

    public:
        ServiceNode(Node*);
        virtual ~ServiceNode();

        virtual void question();
        
    private:
};

#endif