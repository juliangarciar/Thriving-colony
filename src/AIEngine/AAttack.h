#ifndef AATTACK_H
#define AATTACK_H

#include "Action.h"

/**
 * @class AAttack
 * @brief Crea un objeto tipo AAttack
 */
class AAttack : public Action {
    
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
        Enumeration::BehaviourState Update(Enumeration::UnitType);
        Enumeration::BehaviourState Update(Enumeration::BuildingType);

    private:
};

#endif