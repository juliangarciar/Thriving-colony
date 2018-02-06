#include "StartMenu.h"
#include "Game.h"

#include <string>

StartMenu::StartMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<int>(600, 400));

    buttonStart = new Button("Play");
    buttonStart -> setPosition(Vector2<int>(600, 300));    
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