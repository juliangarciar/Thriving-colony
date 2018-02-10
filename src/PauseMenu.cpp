#include "PauseMenu.h"
#include "Game.h"

#include <string>

PauseMenu::PauseMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<i32>(600, 400));

    buttonResume = new Button("Resume game");
    buttonResume -> setPosition(Vector2<i32>(600, 200));

    buttonMenu = new Button("Main menu");
    buttonMenu -> setPosition(Vector2<i32>(600, 300));
}

PauseMenu::~PauseMenu() {
    delete buttonQuit;
    delete buttonResume;
    delete buttonMenu;
}

void PauseMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonResume -> setCallback([]{
        Game::Instance() -> getGameState() -> cleanGamePaused();
    });

    buttonMenu -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::MenuState);
    });
}

void PauseMenu::update() {

}