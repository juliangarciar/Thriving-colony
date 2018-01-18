#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() : State() {
    hud = new HudMenu();
    
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

MenuState::~MenuState() {
    delete hud;
}

void MenuState::init() {

}

void MenuState::input() {
    hud -> getHUDEvents();
    hud -> update();
}

void MenuState::update() {
    Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud -> updatePositions();
    }
}

void MenuState::render() {

}

void MenuState::cleanUp() {

}