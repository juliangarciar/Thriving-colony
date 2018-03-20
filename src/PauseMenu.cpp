#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu() {
    bgMenu = new Panel("Game paused");
    bgMenu -> setPosition(Vector2<i32>(400, 200));
    bgMenu -> setSize(Vector2<i32>(400, 300));
    bgMenu -> setVerticalLayout();


    buttonResume = new Button(bgMenu, "Resume game");
    buttonResume -> setPosition(Vector2<i32>(600, 200));

    buttonMenu = new Button(bgMenu, "Main menu");
    buttonMenu -> setPosition(Vector2<i32>(600, 300));
    
    buttonQuit = new Button(bgMenu, "Quit");
    buttonQuit -> setPosition(Vector2<i32>(600, 400));
    Window::Instance() -> setGUI();
}

PauseMenu::~PauseMenu() {
    delete bgMenu;
    delete buttonQuit;
    delete buttonResume;
    delete buttonMenu;
}

void PauseMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Window::Instance() -> close();
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