#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <sstream>
#include "State.h"
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include "CameraController.h"
#include "BuildingManager.h"
#include "Hud.h"
#include "IAEngine/RootNode.h"
#include "BattleManager.h"

class GameState : public State {
    
    public:
        GameState();
        virtual ~GameState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

        Terrain* getMap();
        Hud* getHud();
        BattleManager* getBattleManager();
        
    private:
        CameraController *camera;
        Terrain *map;
        Hud * hud;
        // This is for pausing, in a future it will be a gamestate different?
        bool gamePaused;

        BattleManager *battleManager;

        int prevWindowWidth, prevWindowHeight;
};

#endif