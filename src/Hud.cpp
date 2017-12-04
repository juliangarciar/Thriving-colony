#include "Hud.h"
#include "Game.h"

using namespace irr;

Hud::Hud() {
    buildingMode = false;
    buttonBuilding = new Button(Rect<int>(700, 600, 200, 60), GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonBuilding = new Button(Rect<int>(950, 600, 200, 60), GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
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
        /*case GUI_ID_QUIT_BUTTON:
            sc->getDevice()->closeDevice();
            std::cout<<"entra en quit button"<<std::endl;
            //Context.listbox->addItem(L"Window created");
            //std::cout<<"x: "<<x<<std::endl;
            //std::cout<<"y: "<<y<<std::endl;
            //std::cout<<"z: "<<z<<std::endl;
            //std::cout<<id<<std::endl;
            //std::cout<<"id GUI: "<<GUI_ID_BUILDING_BUTTON<<std::endl;
            //return true;
        break;*/
    }
}

void Hud::drawCube(Terrain *terrain){
    Game *g = Game::Instance();
    if (buildingMode){
        // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.
        Vector3<float> xyzPointCollision = terrain->getPointCollision(g->getCursor());
        
        if(cubeNode) {
            cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
            cubeNode->setPosition(core::vector3df(xyzPointCollision.x,xyzPointCollision.y,xyzPointCollision.z));
        }
    }
    if (g->getIO()->leftMouseDown()){
        buildingMode = false;
    }
}