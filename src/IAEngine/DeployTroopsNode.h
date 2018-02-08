#ifndef DEPLOY_TROOPS_NODE_H
#define DEPLOY_TROOPS_NODE_H

#include "Node.h"
#include <Types.h>

class DeployTroopsNode : public Node {

    public:
        DeployTroopsNode(Node*);
        virtual ~DeployTroopsNode();

        virtual void question();
        
    private:
};

#endif