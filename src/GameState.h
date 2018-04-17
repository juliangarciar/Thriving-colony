#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "BattleManager.h"
#include "Hud.h"
#include "PauseMenu.h"
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
        * @brief Get the battle manager.
        * @return Pointer to a BattleManager object that will be the value of battleManager variable.
        */
        BattleManager* getBattleManager();

        /**
         * @brief Delete pauseMenu variable and set gamePaused as false.
         */
        void cleanGamePaused();

        /* Added by Juli */
        void setRaces(std::string _iaRace, std::string _humanRace);
    private:
        //Pointer to the human player's object.
        Human *human;

        //Pointer to the AI player's object.
        IA *ia;

        //Pointer to the map that will be used.
        Map *map;

        //Pointer to the hud that will be used.
        Hud *hud;

        //Pointer to the hud of pause mode.
        PauseMenu *pauseMenu;
        
        //Pointer to the battle manager.
        BattleManager *battleManager;

        //True when the game is paused and false in other case.
        bool gamePaused;

        /* Added by Julian */
        std::string humanRace;
        std::string iaRace;
};

#endif