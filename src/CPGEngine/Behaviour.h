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

        Enumeration::BehaviourState virtual Update() = 0;
        Enumeration::BehaviourState getState();

    protected:
        Enumeration::BehaviourState state;

};

#endif