#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<i32>(600, 400));

    buttonStart = new Button("Play");
    buttonStart -> setPosition(Vector2<i32>(600, 300)); 
    Window::Instance() -> setGUI();   
}

StartMenu::~StartMenu() {
    delete buttonQuit;
    delete buttonStart;
}

void StartMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonStart -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::GameState);
    });
}

void StartMenu::update() {

}