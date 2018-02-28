#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include "Behaviour.h"

/**
 * @class Composite
 * @brief Crea un objeto tipo Composite
 */
class Composite : Behaviour {
    
    public:
        /**
         * @brief Constructor de Composite
         */
        Composite(std::vector<Behaviour*>);
        /**
         * @brief Destructor de Composite
         */
        virtual ~Composite();

    private:
        std::vector<Behaviour*> children;

};

#endif