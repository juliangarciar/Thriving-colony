#ifndef MARKET_NODE_H
#define MARKET_NODE_H

#include "Node.h"
#include <Types.h>

class MarketNode : public Node {

    public:
        MarketNode(Node*);
        virtual ~MarketNode();

        virtual void question();
        
    private:
};

#endif