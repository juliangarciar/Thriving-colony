#include "HudPause.h"
#include "Game.h"

#include <string>

HudPause::HudPause() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<int>(600, 400));

    buttonResume = new Button("Resume game");
    buttonResume -> setPosition(Vector2<int>(600, 200));

    buttonMenu = new Button("Main menu");
    buttonMenu -> setPosition(Vector2<int>(600, 300));
}

HudPause::~HudPause() {
    delete buttonQuit;
    delete buttonResume;
    delete buttonMenu;
}

void HudPause::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonResume -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::GameState);
    });

    buttonMenu -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::MenuState);
    });
}

void HudPause::update() {

}