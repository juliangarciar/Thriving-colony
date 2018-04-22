#ifndef AATTACK_H
#define AATTACK_H

#include "Action.h"

/**
 * @class AAttack.
 * @brief Create a AAttack type object. Public heritage from Action class.
 */
class AAttack : public Action {
    
    public:
        /**
         * @brief AAttack constructor.
         */
        AAttack();

        /**
         * @brief AAttack destructor.
         */
        virtual ~AAttack();

        /**
         * @brief 
         * 
         * @return Enumeration::BehaviourState 
         */
        Enumeration::BehaviourState Update();

        /**
         * @brief 
         * 
         * @return Enumeration::BehaviourState 
         */
        Enumeration::BehaviourState Update(Enumeration::UnitType);

        /**
         * @brief 
         * 
         * @return Enumeration::BehaviourState 
         */
        Enumeration::BehaviourState Update(Enumeration::BuildingType);

    private:
};

#endif