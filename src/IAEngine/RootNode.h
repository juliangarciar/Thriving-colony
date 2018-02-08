#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "Node.h"
#include "../Enumeration.h"
#include <Types.h>

class RootNode : public Node {

    public:
        RootNode();
        virtual ~RootNode();

        virtual void question();

        void init(Enumeration::IABehaviour);
    private:
};

#endif