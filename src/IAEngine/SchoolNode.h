#ifndef SCHOOL_NODE_H
#define SCHOOL_NODE_H

#include "Node.h"

class SchoolNode : public Node {

    public:
        SchoolNode(Node *);
        virtual ~SchoolNode();

        virtual void question();
        
    private:
};

#endif