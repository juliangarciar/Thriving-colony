#ifndef WORKSHOP_NODE_H
#define WORKSHOP_NODE_H

#include "Node.h"
#include <Types.h>

class WorkshopNode : public Node {

    public:
        WorkshopNode(Node *);
        virtual ~WorkshopNode();

        virtual void question();
        
    private:
};

#endif