#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() : State() {
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

MenuState::~MenuState() {
}

void MenuState::Init() {
    hud = new StartMenu();
    Window::Instance() -> setGUI();
    
    hud -> setHUDEvents();
}

void MenuState::Input() {
    hud -> update();
}

void MenuState::Update() {
    /*Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }*/
}

void MenuState::Render() {

}

void MenuState::CleanUp() {
    delete hud;
    Window::Instance() -> setGUI();
}