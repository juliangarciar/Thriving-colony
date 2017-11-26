#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
    
    public:
        Human();
        virtual ~Human();
        static Human* getInstance();

    private:
        static Human* instance;
            
};

#endif