#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "../Enumeration.h"

/**
 * @class Behaviour
 * @brief Crea un objeto tipo Behaviour
 */
class Behaviour {
    
    public:
        /**
         * @brief Constructor de Behaviour
         */
        Behaviour();
        /**
         * @brief Destructor de Behaviour
         */
        virtual ~Behaviour();

        Enumeration::BehaviourState Update();
        Enumeration::BehaviourState getState();

    private:
        Enumeration::BehaviourState state;

};

#endif