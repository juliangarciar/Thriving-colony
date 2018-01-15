#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Hud.h"

class MenuState : public State {
    
    public:
        MenuState();
        virtual ~MenuState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

    private:
        Hud * hud;

        int prevWindowWidth;
        int prevWindowHeight;
};

#endif