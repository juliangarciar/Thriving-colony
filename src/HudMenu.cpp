#include "HudMenu.h"
#include "Game.h"

#include <string>

HudMenu::HudMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<int>(600, 400));

    buttonStart = new Button("Play");
    buttonStart -> setPosition(Vector2<int>(600, 300));    
}

HudMenu::~HudMenu() {
    delete buttonQuit;
    delete buttonStart;
}

void HudMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonStart -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::GameState);
    });
}

void HudMenu::update() {

}