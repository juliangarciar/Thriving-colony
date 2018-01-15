#include "HudMenu.h"
#include "Game.h"

#include <string>

HudMenu::HudMenu() {
    //Le botone iniciale
    buttonQuit = new Button(Rect2D<int>(1150, 20, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
}

HudMenu::~HudMenu() {
    //Los dos botones iniciales
    delete buttonQuit;
}

void HudMenu::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g -> getIO() -> getGUIClickedID();

    switch(id){
        //Le botone iniciale
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g -> getWindow() -> getDevice() -> closeDevice();
        break;
    }
}

void HudMenu::update() {

}

void HudMenu::updatePositions(){
    buttonQuit->setPosition(Vector2<int>(1150, 20).getFixed());
}
