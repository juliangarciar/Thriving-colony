#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() : State() {
    hud = new StartMenu();
    Window::Instance() -> setGUI();
    
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

MenuState::~MenuState() {
    delete hud;
}

void MenuState::init() {
    hud -> setHUDEvents();
}

void MenuState::input() {
    hud -> update();
}

void MenuState::update() {
    /*Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }*/
}

void MenuState::render() {

}

void MenuState::cleanUp() {

}