#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "CameraController.h"
#include "GraphicEngine/Terrain.h"
#include "IOEngine/InputManager.h"

class GameState : public State {
    
    public:
        GameState();
        ~GameState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

    private:
        CameraController *camera;
        Terrain *map;
        Mouse *cursor;
};

#endif