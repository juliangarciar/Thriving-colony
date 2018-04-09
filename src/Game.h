#ifndef GAME_H
#define GAME_H

#include <IOEngine/IO.h>

#include <GraphicEngine/Window.h>

#include <SoundEngine/SoundSystem.h>

#include <Enumeration.h>
#include <Types.h>

#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "WinState.h"
#include "DefeatState.h"

/**
 * @class Game.
 * @brief Create a Game type object. Singleton class.
 */
class Game {
    public:

        /**
		 * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * @return Pointer to a Game object that will be the value of pinstance variable.
		 */
        static Game* Instance();

        /**
		 * @brief Initialize state variable.
		 */
        void Init();

        /**
		 * @brief Get the inputs from state variable and the mouse.
		 */
        void Input();

        /**
		 * @brief Update state variable.
		 */
        void Update();

        /**
		 * @brief Render state variable.
		 */
        void Render();

        /**
		 * @brief Delete state and close the window.
		 */
        void CleanUp();

        /**
        * @brief Change the state variable to the state passed by parameter.
        * @param The Enumeration::State is the new state to which is going to change the game. 
        */
        void changeState(Enumeration::State);

        /**
		 * @brief Get menu state.
         * @return Pointer to a MenuState object that will be the value of menu variable.
		 */
        MenuState *getMenuState();

         /**
		 * @brief Get game state.
         * @return Pointer to a GAmeState object that will be the value of game variable.
		 */
		GameState *getGameState();

    protected:

        /**
		 * @brief Game constructor.
		 */
        Game();

        /**
		 * @brief Game destructor.
		 */
        virtual ~Game();
        
        /**
		 * @brief Redefine iqual operator.
		 */
        Game &operator = (const Game & );

    private:

        //Pointer to the only instance of Game class.
        static Game* pinstance;

        //Current state of the game.
        State *state;

        //Current state of the game.
        Enumeration::State stateData;

        //Pointer to main menu state of the game.
        MenuState *menu;

        //Pointer to the game of the game.
        GameState *game;

        //Pointer to the win menu of the game.
        WinState *win;

        //Pointer to the defeat menu of the game.
        DefeatState *defeat;
        
        //Pointer to the window of the game.
        Window *window;

        //Pointer to the IO of the game.
        IO *io;
        
        //Pointer to the sound system of the game.
        SoundSystem *soundSystem;
        
};

#endif