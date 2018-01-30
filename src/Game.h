#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "IOEngine/EventSystem.h"

#include <IOEngine/Mouse.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/EventSystem.h>
#include <GraphicEngine/Window.h>

#include <SoundEngine/SoundSystem.h>

/**
 * @class Game
 * @brief Esta clase hace algo
 */
class Game {
    public:
        /**
		 * @brief Metodo que hace algo
		 */
        static Game* Instance();

        /**
		 * @brief Metodo que hace algo
		 */
        void init();
        /**
		 * @brief Metodo que hace algo
		 */
        void input();
        /**
		 * @brief Metodo que hace algo
		 */
        void update();
        /**
		 * @brief Metodo que hace algo
		 */
        void render();
        /**
		 * @brief Metodo que hace algo
		 */
        void cleanUp();
        /**
		 * @brief Metodo que hace algo
		 */
        void changeState(Enumeration::State);

        /**
		 * @brief Metodo que hace algo
		 */
        Window *getWindow();
        /**
		 * @brief Metodo que hace algo
		 */
        Keyboard *getKeyboard();
        Mouse *getCursor();
        /**
		 * @brief Metodo que hace algo
		 */
        EventSystem *getEvents();
        /**
		 * @brief Metodo que hace algo
		 */
        MenuState *getMenuState();
        /**
		 * @brief Metodo que hace algo
		 */
		GameState *getGameState();
        
    protected:
        /**
		 * @brief Constructor por defecto.
		 */
        Game();
        /**
		 * @brief Destructor.
		 */
        virtual ~Game();
        /**
		 * @brief No se que hace
		 */
        Game(const Game & );
        /**
		 * @brief Tampoco se que hace
		 */
        Game &operator = (const Game & );

    private:
        static Game* pinstance;

        State *state;
        Window *window;
        Enumeration::State stateData;

        MenuState *menu;
        GameState *game;
        PauseState *pause;

        Mouse *cursor;
        Keyboard *keyboard;

        EventSystem *events;
        
        SoundSystem *soundSystem;
};

#endif