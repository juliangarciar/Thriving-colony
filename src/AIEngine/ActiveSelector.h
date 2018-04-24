#ifndef ACTIVESELECTOR_H
#define ACTIVESELECTOR_H

#include "Selector.h"
#include "Behaviour.h"

/**
 * @class ActiveSelector.
 * @brief Create a ActiveSelector type object. Public heritage from Selector class.
 */
class ActiveSelector : public Selector {
    
    public:
        /**
         * @brief ActiveSelector constructor.
         */
        ActiveSelector(std::vector<Behaviour*>);

        /**
         * @brief ActiveSelector destructor.
         */
        virtual ~ActiveSelector();
        
        /**
         * @brief When it has a priority call its Update method and when it has not call the Selector Update method.
         * 
         * @return Enumeration::BehaviourState::Success when the Update has been done and Enumeration::BehaviourState::Failure in other case.
         * @see Update() method from Selector class.
         */
        Enumeration::BehaviourState Update();

        /**
         * @brief Set the priority to a new priority choice.
         * 
         * @param Behaviour is the new value for priority variable.
         */
        void setPriority(Behaviour*);

        /**
         * @brief Get the value of the priority choice.
         * 
         * @return Pointer to a Behaviour object that will be the value of priority variable.
         */
        Behaviour* getPriority();

    private:
        //Pointer to the priority choice of the IA. It can be nullptr.
        Behaviour* priority;

};

#endif