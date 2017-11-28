#ifndef ATTACK_UNIT_ROOT_H
#define ATTACK_UNIT_ROOT_H

#include "Node.h"

class AttackUnitRoot : public Node {

    public:
        AttackUnitRoot();
        virtual ~AttackUnitRoot();

    private:
        virtual void question();
};

#endif