#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Rect.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>
#include <GraphicEngine/Button.h>

using namespace irr;

class Hud {
    
    public:
        Hud();
        ~Hud();

        void showHud();
        void drawCube(InputManager *receiver, Mouse *cursor, Terrain *terrain);

    private:
        enum idGUI {
            ID0,
            GUI_ID_BUILDING_BUTTON,
            GUI_ID_QUIT_BUTTON
        };
        idGUI idButtonGUI;
        int id;
        int counter;
        Vector3<float> xyzPointCollision;
        Button * buttonBuilding;    
        
};

#endif