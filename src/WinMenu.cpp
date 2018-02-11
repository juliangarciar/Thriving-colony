#include "WinMenu.h"
#include "Game.h"

WinMenu::WinMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<int>(600, 400));

    buttonStart = new Button("Main Menu");
    buttonStart -> setPosition(Vector2<int>(600, 300));

    winText = new Label("Victory");
    Window::Instance() -> setGUI();
}

WinMenu::~WinMenu() {
    delete buttonQuit;
    delete buttonStart;
}

void WinMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonStart -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::MenuState);
    });
}

void WinMenu::update() {

}