#ifndef HOSPITAL_NODE_H
#define HOSPITAL_NODE_H

#include "Node.h"

class HospitalNode : public Node {

    public:
        HospitalNode(Node*);
        ~HospitalNode();

    private:
        virtual void question();
};

#endif