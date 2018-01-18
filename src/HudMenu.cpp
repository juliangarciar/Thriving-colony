#include "HudMenu.h"
#include "Game.h"

#include <string>

HudMenu::HudMenu() {
    buttonQuit = new Button(Rect2D<int>(500, 400, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    buttonStart = new Button(Rect2D<int>(500, 300, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_PLAY_BUTTON, L"Play", L"Play Game");
}

HudMenu::~HudMenu() {
    delete buttonQuit;
    delete buttonStart;
}

void HudMenu::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g -> getIO() -> getGUIClickedID();
    switch (id) {
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g -> getWindow() -> getDevice() -> closeDevice();
        break;

        case Enumeration::idGUI::GUI_ID_PLAY_BUTTON:
            g -> changeState(Enumeration::State::GameState);
        break;
    }
}

void HudMenu::update() {

}

void HudMenu::updatePositions(){
    buttonQuit -> setPosition(Vector2<int>(500, 400).getFixed());
    buttonStart -> setPosition(Vector2<int>(500, 300).getFixed());
}