#ifndef AATTACK_H
#define AATTACK_H

#include "Action.h"

/**
 * @class AAttack
 * @brief Crea un objeto tipo AAttack
 */
class AAttack : Action {
    
    public:
        /**
         * @brief Constructor de AAttack
         */
        AAttack();
        /**
         * @brief Destructor de AAttack
         */
        virtual ~AAttack();

        Enumeration::BehaviourState Update();
        void Execute();

    private:
};

#endif