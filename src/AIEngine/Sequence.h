#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Composite.h"

/**
 * @class Sequence
 * @brief Crea un objeto tipo Sequence
 */
class Sequence : public Composite {
    
    public:
        /**
         * @brief Constructor de Sequence
         */
        Sequence(std::vector<Behaviour*>);
        /**
         * @brief Destructor de Sequence
         */
        virtual ~Sequence();

    private:

};

#endif