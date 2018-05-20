#include "WinMenu.h"
#include "Game.h"

WinMenu::WinMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<i32>(600, 400));

    buttonStart = new Button("Main Menu");
    buttonStart -> setPosition(Vector2<i32>(600, 300));

    winText = new Label("Victory");
    Window::Instance() -> setGUI();
}

WinMenu::~WinMenu() {
    delete buttonQuit;
    delete buttonStart;
    delete winText;
}

void WinMenu::setHUDEvents() {
    buttonQuit -> setCallback([]{
        Window::Instance() -> close();
    });

    buttonStart -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::MenuState);
    });
}