#ifndef ACTIVESELECTOR_H
#define ACTIVESELECTOR_H

#include "Selector.h"
#include "Behaviour.h"

/**
 * @class ActiveSelector
 * @brief Crea un objeto tipo ActiveSelector
 */
class ActiveSelector : Selector {
    
    public:
        /**
         * @brief Constructor de ActiveSelector
         */
        ActiveSelector(std::vector<Behaviour*>);
        /**
         * @brief Destructor de ActiveSelector
         */
        virtual ~ActiveSelector();

        Enumeration::BehaviourState Update();
        void setPriority(Behaviour*);

    private:
        Behaviour *priority;

};

#endif