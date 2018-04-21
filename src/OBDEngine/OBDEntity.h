#ifndef OBDENTITY_H
#define OBDENTITY_H

#include "OBDTypes.h"
#include "OBDEnums.h"
#include "Graphics/TNode.h"

class OBDEntity {
    public:
        virtual TNode *getFirstNode() = 0;

};

#endif