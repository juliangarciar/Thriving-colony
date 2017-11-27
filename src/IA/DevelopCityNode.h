#ifndef DEVELOP_CITY_NODE_H
#define DEVELOP_CITY_NODE_H

#include "Node.h"

class DevelopCityNode : public Node {

    public:
        DevelopCityNode(Node*);
        virtual ~DevelopCityNode();

    private:
        virtual void question();
};

#endif