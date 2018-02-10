#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <Types.h>

class Human : public Player {
    public:
        static Human* Instance();

        void Init();
        void Update();
        void CleanUp();

        bool getUnderAttack();
    protected:
        Human();
        virtual ~Human();

    private:
        static Human* instance;
};

#endif
