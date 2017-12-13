#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include "CameraController.h"
#include "BuildingManager.h"
#include "Hud.h"
<<<<<<< HEAD
#include "UnitManager.h"
=======
#include "IAEngine/RootNode.h"
>>>>>>> master

class GameState : public State {
    
    public:
        GameState();
        ~GameState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();
        
<<<<<<< HEAD
		BuildingManager *getBuildingManager();
        //Returns the unit manager 
        UnitManager* getUnitManager();
=======
>>>>>>> master
    private:
        CameraController *camera;
        Terrain *map;
        Hud * hud;
<<<<<<< HEAD
		BuildingManager *buildingManager;
        //Needed for unit creation
        UnitManager* unitManager;
=======
        RootNode *nodeRootIA;
>>>>>>> master
};

#endif