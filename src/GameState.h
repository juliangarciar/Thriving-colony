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
#include "SoundEngine/Music.h"

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
        
    private:
    //Music try
        Music *music;
    //
        CameraController *camera;
        Terrain *map;
        Hud * hud;
        // ESTO NO VA A QUI POR QUE ESTA AQUIIIIIIIIIIIIIIIIIIIII
        // PERO YA QUE ESTAMOS VOY A ECHAR MAS SPAGUETTI LLAMADLE ILL CHEFF RAFAELO
        float iaUpdateTimer;
        RootNode *nodeRootIA;
        // This is for pausing, in a future it will be a gamestate different?
        bool gamePaused;
        Music *MusicSystem;
};

#endif