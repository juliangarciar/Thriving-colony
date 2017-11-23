#ifndef WORKSHOP_NODE_H
#define WORKSHOP_NODE_H

#include "Node.h"

class WorkshopNode : public Node {

    public:
        WorkshopNode(Node *);
        ~WorkshopNode();

    private:
        virtual void question();
};

#endif