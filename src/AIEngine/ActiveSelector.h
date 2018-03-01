#ifndef ACTIVESELECTOR_H
#define ACTIVESELECTOR_H

#include "Selector.h"

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

    private:

};

#endif