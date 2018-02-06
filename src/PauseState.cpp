#include "PauseState.h"
#include "Game.h"

PauseState::PauseState() : State() {
    hud = new PauseMenu();
    Window::Instance() -> setGUI();
    
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

PauseState::~PauseState() {
    delete hud;
}

void PauseState::init() {
    hud -> setHUDEvents();
}

void PauseState::input() {
    hud -> update();
}

void PauseState::update() {
    /*Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }*/
}

void PauseState::render() {

}

void PauseState::cleanUp() {

}