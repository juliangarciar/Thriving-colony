#ifndef HOME_NODE_H
#define HOME_NODE_H

#include "Node.h"
#include <Types.h>

class HomeNode : public Node {

    public:
        HomeNode(Node*);
        virtual ~HomeNode();

        virtual void question();
        
    private:
};

#endif