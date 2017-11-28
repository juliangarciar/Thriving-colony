#ifndef MARKET_NODE_H
#define MARKET_NODE_H

#include "Node.h"

class MarketNode : public Node {

    public:
        MarketNode(Node*);
        virtual ~MarketNode();

    private:
        virtual void question();
};

#endif