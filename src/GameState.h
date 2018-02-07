#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <sstream>
#include "IA.h"
#include "Hud.h"
#include "Human.h"
#include "State.h"
#include "CameraController.h"
#include "BuildingManager.h"
#include "BattleManager.h"

#include <IAEngine/RootNode.h>

#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>

#include <SoundEngine/SoundSystem.h>
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
        void init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void input();
        /**
		 * @brief Actualiza
		 */
        void update();
        /**
		 * @brief Renderiza
		 */
        void render();
        /**
		 * @brief Constructor
		 */
        void cleanUp();
        /**
        * @brief Devuelve el mapa
        * @return objeto de tipo Terrain
        */
        Terrain* getTerrain();
         /**
        * @brief Devuelve la interfaz
        * @return objeto de tipo Hud
        */
        Hud* getHud();
         /**
        * @brief Devuelve el manejador de batalla
        * @return objeto de tipo BattleManager
        */
        BattleManager* getBattleManager();
        
    private:
        Light *light;
        CameraController *camera;
        Terrain *map;
        Hud * hud;
        BattleManager *battleManager;

        // This is for pausing, in a future it will be a gamestate different?
        bool gamePaused;

        int prevWindowWidth, prevWindowHeight;
};

#endif