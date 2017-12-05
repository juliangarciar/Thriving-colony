#include "Hud.h"
#include "Game.h"

using namespace irr;

Hud::Hud() {
    buildingMode = false;
    buttonBuilding = new Button(Rect<int>(700, 600, 200, 60), GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonBuilding = new Button(Rect<int>(950, 600, 200, 60), GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

    gridAlignment = 50;
}

Hud::~Hud() {
     
}

void Hud::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g->getIO()->getGUIClickedID();
    switch(id){
        case GUI_ID_BUILDING_BUTTON:
            buildingMode = true;
            cubeNode = g->getWindow()->getSceneManager()->addCubeSceneNode(100);
        break;
        case GUI_ID_QUIT_BUTTON:
            g->getWindow()->getDevice()->closeDevice();
        break;
    }
}

void Hud::drawCube(Terrain *terrain){
    Game *g = Game::Instance();
    if (buildingMode){
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
        Vector3<float> xyzPointCollision = terrain->getPointCollision(g->getCursor());
        
        float x = roundf(xyzPointCollision.x/gridAlignment)*gridAlignment;
        float y = roundf(xyzPointCollision.y/gridAlignment)*gridAlignment;
        float z = roundf(xyzPointCollision.z/gridAlignment)*gridAlignment;
        //ToDo: irr::core::aabbox3d< T >
        if(cubeNode) {
            cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
            cubeNode->setPosition(core::vector3df(x,y,z));
        }
    }
    if (g->getIO()->leftMouseDown()){
        buildingMode = false;
    }
}