#ifndef DEPLOY_TROOPS_NODE_H
#define DEPLOY_TROOPS_NODE_H

#include "Node.h"

class DeployTroopsNode : public Node {

    public:
        DeployTroopsNode(Node*);
        virtual ~DeployTroopsNode();

    private:
        virtual void question();
};

#endif