#ifndef CRIATURE_NODE_H
#define CRIATURE_NODE_H

#include "Node.h"

class CriatureNode : public Node {

    public:
        CriatureNode(Node *);
        ~CriatureNode();

    private:
        virtual void question();
};

#endif