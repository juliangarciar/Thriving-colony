#include "HudPause.h"
#include "Game.h"

#include <string>

HudPause::HudPause() {
    buttonQuit = new Button(Rect2D<int>(500, 500, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    buttonResume = new Button(Rect2D<int>(500, 300, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_RESUME_BUTTON, L"Resume", L"Resume Game");
    buttonMenu = new Button(Rect2D<int>(500, 400, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_MENU_BUTTON, L"Main menu", L"Go to main menu");
}

HudPause::~HudPause() {
    delete buttonQuit;
    delete buttonResume;
    delete buttonMenu;
}

void HudPause::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g -> getIO() -> getGUIClickedID();
    switch (id) {
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g -> getWindow() -> getDevice() -> closeDevice();
        break;

        case Enumeration::idGUI::GUI_ID_RESUME_BUTTON:
            g -> changeState(Enumeration::State::GameState);
        break;

        case Enumeration::idGUI::GUI_ID_MENU_BUTTON:
            g -> changeState(Enumeration::State::MenuState);
        break;
    }
}

void HudPause::update() {

}

void HudPause::updatePositions(){
    buttonQuit -> setPosition(Vector2<int>(500, 500).getFixed());
    buttonResume -> setPosition(Vector2<int>(500, 300).getFixed());
    buttonMenu -> setPosition(Vector2<int>(500, 400).getFixed());
}