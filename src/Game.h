#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "MenuState.h"
#include "GameState.h"

#include <IOEngine/InputManager.h>
#include <GraphicEngine/Screen.h>

class Game {
    public:
        static Game* Instance();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

        Screen *getWindow();
        InputManager *getIO();

    protected:
        Game();
        virtual ~Game();
        Game(const Game & );
        Game &operator = (const Game & );

    private:
        static Game* pinstance;
        State *state;
        Screen *window;

        MenuState *menu;
        GameState *game;

        InputManager *io;
};

#endif