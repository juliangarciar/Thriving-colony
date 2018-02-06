#include "PauseState.h"
#include "Game.h"

PauseState::PauseState() : State() {
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

PauseState::~PauseState() {
}

void PauseState::Init() {
    hud = new PauseMenu();
    Window::Instance() -> setGUI();
    
    hud -> setHUDEvents();
}

void PauseState::Input() {
    hud -> update();
}

void PauseState::Update() {
    /*Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }*/
}

void PauseState::Render() {

}

void PauseState::CleanUp() {
    delete hud;
    Window::Instance() -> setGUI();
}