#ifndef CATTACK_H
#define CATTACK_H

#include "Condition.h"

/**
 * @class CAttack
 * @brief Crea un objeto tipo CAttack
 */
class CAttack : public Condition {
    
    public:
        /**
         * @brief Constructor de CAttack
         */
        CAttack(Action*);
        /**
         * @brief Destructor de CAttack
         */
        virtual ~CAttack();

        Enumeration::BehaviourState Update();

    private: 
};

#endif