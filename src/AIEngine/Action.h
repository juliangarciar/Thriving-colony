#ifndef ACTION_H
#define ACTION_H

#include "Behaviour.h"

/**
 * @class Action
 * @brief Crea un objeto tipo Action
 */
class Action : public Behaviour {
    
    public:
        /**
         * @brief Constructor de Action
         */
        Action();
        /**
         * @brief Destructor de Action
         */
        virtual ~Action();

        Enumeration::BehaviourState virtual Update() = 0;
        Enumeration::BehaviourState virtual Update(Enumeration::UnitType) = 0;
        Enumeration::BehaviourState virtual Update(Enumeration::BuildingType) = 0;

    protected:
};

#endif