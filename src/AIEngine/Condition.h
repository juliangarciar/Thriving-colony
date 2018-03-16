#ifndef CONDITION_H
#define CONDITION_H

#include "Behaviour.h"
#include "Action.h"

/**
 * @class Condition
 * @brief Crea un objeto tipo Condition
 */
class Condition : public Behaviour {
    
    public:
        /**
         * @brief Constructor de Condition
         */
        Condition(Action*);
        /**
         * @brief Destructor de Condition
         */
        virtual ~Condition();

        Enumeration::BehaviourState virtual Update() = 0;

    protected:
        Action* action;
};

#endif