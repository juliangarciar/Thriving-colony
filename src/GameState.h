#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

#include "Hud.h"
#include "PauseMenu.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "BattleManager.h"

#include <Types.h>

/**
 * @class GameState
 * @brief Tiene herencia publica de State y crea un objeto tipo GameState
 */
class GameState : public State {
    public:
        /**
		 * @brief Constructor de GameState
		 */
        GameState();
        /**
		 * @brief Destructor
		 */
        virtual ~GameState();

         /**
		 * @brief Inicializa GameState
		 */
        void Init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void Input();
        /**
		 * @brief Actualiza
		 */
        void Update();
        /**
		 * @brief Renderiza
		 */
        void Render();
        /**
		 * @brief Constructor
		 */
        void CleanUp();
        
         /**
        * @brief Devuelve el manejador de batalla
        * @return objeto de tipo BattleManager
        */
        BattleManager* getBattleManager();

        /**
         * @brief 
         * 
         */
        void cleanGamePaused();
    private:
        //Singletons
        Human *human;
        IA *ia;
        Map *map;
        Hud *hud;

        //Pause
        PauseMenu *pauseMenu;
        
        //Battles
        BattleManager *battleManager;

        // This is for pausing
        bool gamePaused;
};

#endif