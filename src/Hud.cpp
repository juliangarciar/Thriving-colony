#include "Hud.h"
#include "GraphicEngine/Screen.h"

using namespace irr;

Hud::Hud() {
    
}

Hud::~Hud() {
    
}

void Hud::showHud(){
    Screen *sc = Screen::Instance();
    sc->getGUIEnvironment()->addButton(core::rect<s32>(core::position2d<s32>(540, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits Program");
    sc->getGUIEnvironment()->addButton(core::rect<s32>(core::position2d<s32>(540, 350), core::dimension2d<s32>(200, 60)), 0, GUI_ID_NEW_WINDOW_BUTTON,
            L"New Window", L"Launches a new Window");
    sc->getGUIEnvironment()->addButton(core::rect<s32>(core::position2d<s32>(1040, 630), core::dimension2d<s32>(200, 60)), 0, GUI_ID_FILE_OPEN_BUTTON,
            L"File Open", L"Opens a file");
}

void Hud::drawCube(InputManager *receiver, Mouse *cursor, Terrain *terrain){
    Screen *sc = Screen::Instance();
    counter = 0;
    id = receiver->getGUIID();

    switch(id){
        case GUI_ID_QUIT_BUTTON:
            //sc->getDevice()->closeDevice();
            std::cout<<"entra en quit button"<<std::endl;
            //return true;
        break;

        case GUI_ID_NEW_WINDOW_BUTTON:
        std::cout<<"entra en window button"<<std::endl;
            //Context.listbox->addItem(L"Window created");
            counter += 200;
            if (counter > 5000)
                counter = 0;
            
            // Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
            // tambien se cree una caja en las coordenadas actuales del cursor del raton.
            xyzPointCollision = terrain->getPointCollision(cursor);
            /*x = xyzPointCollision.x;
            y = xyzPointCollision.y;
            z = xyzPointCollision.z;*/
            
            /*scene::IMeshSceneNode *cubeNode = sc->getSceneManager()->addCubeSceneNode(100);

            if(cubeNode) {
                cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
                cubeNode->setPosition(core::vector3df(500 + counter,500,2500));
            }*/
        break;
    }
}