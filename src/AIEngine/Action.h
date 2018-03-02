#ifndef ACTION_H
#define ACTION_H

#include "Behaviour.h"

/**
 * @class Action
 * @brief Crea un objeto tipo Action
 */
class Action : Behaviour {
    
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
        void virtual execute() = 0;

    private:
};

#endif