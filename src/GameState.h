#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

#include "Hud.h"
#include "PauseMenu.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"

#include <Types.h>

/**
 * @class GameState.
 * @brief Create a GameState type object. Public heritage from State class.
 */
class GameState : public State {
    public:
        /**
         * @brief GameState constructor.
         */

        GameState();

        /**
         * @brief GameState destructor.
         */
        virtual ~GameState();

         /**
         * @brief Initialize the variables.
         */
        void Init();

        /**
         * @brief Update all inputs of the variables.
         */
        void Input();

        /**
         * @brief Update the variables.
         */
        void Update();

        /**
         * @brief Render.
         */
        void Render();

        /**
         * @brief Delete all variables.
         */
        void CleanUp();

        /**
         * @brief Delete pauseMenu variable and set gamePaused as false.
         */
        void cleanGamePaused();

    private:
        //Pointer to the map that will be used.
        Map *map;

        //Pointer to the hud of pause mode.
        PauseMenu *pauseMenu;

        //True when the game is paused and false in other case.
        bool gamePaused;
};

#endif