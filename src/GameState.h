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

class GameState : public State {
    
    public:
        GameState();
        virtual ~GameState();

        void init();
        void input();
        void update();
        void render();
        void cleanUp();

        Terrain* getMap();
        Hud* getHud();
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