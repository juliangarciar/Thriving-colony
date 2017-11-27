#ifndef HOME_NODE_H
#define HOME_NODE_H

#include "Node.h"

class HomeNode : public Node {

    public:
        HomeNode(Node*);
        virtual ~HomeNode();

    private:
        virtual void question();
};

#endif