#include "Hud.h"
#include "GraphicEngine/Screen.h"

using namespace irr;

Hud::Hud() {
    buttonBuilding = new Button(Rect<int>(700, 600, 200, 60), GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonBuilding = new Button(Rect<int>(950, 600, 200, 60), GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
}

Hud::~Hud() {
    
}

void Hud::showHud(){
   
}

void Hud::drawCube(InputManager *receiver, Mouse *cursor, Terrain *terrain){
    Screen *sc = Screen::Instance();
    counter = 0;
    id = receiver->getGUIID();
    //std::cout<<id<<std::endl;
    int x, y, z;
    //std::cout<<"id GUI: "<<GUI_ID_BUILDING_BUTTON<<std::endl;
    switch(id){

        case GUI_ID_BUILDING_BUTTON:
            std::cout<<"entra en building button"<<std::endl;
            //Context.listbox->addItem(L"Window created");
            counter += 200;
            if (counter > 5000)
                counter = 0;
            
            // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
            // tambien se cree una caja en las coordenadas actuales del cursor del raton.
            xyzPointCollision = terrain->getPointCollision(cursor);
            x = xyzPointCollision.x;
            y = xyzPointCollision.y;
            z = xyzPointCollision.z;
            //std::cout<<"x: "<<x<<std::endl;
            //std::cout<<"y: "<<y<<std::endl;
            //std::cout<<"z: "<<z<<std::endl;
            
            scene::IMeshSceneNode *cubeNode = sc->getSceneManager()->addCubeSceneNode(100);

            if(cubeNode) {
                cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
                cubeNode->setPosition(core::vector3df(x,y,z));
            }
        break;

        /*case GUI_ID_QUIT_BUTTON:
            sc->getDevice()->closeDevice();
            std::cout<<"entra en quit button"<<std::endl;
            //return true;
        break;*/
    }
}