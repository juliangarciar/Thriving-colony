#ifndef CRECRUIT_H
#define CRECRUIT_H

#include "Condition.h"

/**
 * @class CRecruit
 * @brief Crea un objeto tipo CRecruit
 */
class CRecruit : public Condition {
    
    public:
        /**
         * @brief Constructor de CRecruit
         */
        CRecruit(Action*, std::string, i32, i32);
        /**
         * @brief Destructor de CRecruit
         */
        virtual ~CRecruit();

        Enumeration::BehaviourState Update();
        void actionToDo();

    private:
        std::string type;
        i32 metal;
        i32 crystal;
		i32 citizens;
};

#endif