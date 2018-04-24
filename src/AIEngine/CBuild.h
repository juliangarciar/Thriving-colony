#ifndef CBUILD_H
#define CBUILD_H

#include "Condition.h"

/**
 * @class CBuild
 * @brief Crea un objeto tipo CBuild
 */
class CBuild : public Condition {
    
    public:
        /**
         * @brief Constructor de CBuild
         */
        CBuild(Action*, std::string, i32, i32);
        /**
         * @brief Destructor de CBuild
         */
        virtual ~CBuild();

        Enumeration::BehaviourState Update();
        void actionToDo();

    private:
        std::string type;
        i32 metal;
        i32 crystal;
};

#endif