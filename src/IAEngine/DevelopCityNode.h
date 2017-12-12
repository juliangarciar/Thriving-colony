#ifndef DEVELOP_CITY_NODE_H
#define DEVELOP_CITY_NODE_H

#include "Node.h"

class DevelopCityNode : public Node {

    public:
        DevelopCityNode(Node*);
        virtual ~DevelopCityNode();

        virtual void question();
        
    private:
};

#endif