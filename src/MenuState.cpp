#include "MenuState.h"

MenuState::MenuState() : State() {
    hud = new HudMenu();
    
    prevWindowWidth = 1280;
    prevWindowHeight = 720;
}

MenuState::~MenuState() {
    delete hud;
}

void MenuState::Init(){

}

void MenuState::Input(){
    hud -> getHUDEvents();
    hud -> update();
}

void MenuState::Update(){
    Game *g = Game::Instance();
    if (g -> getWindow() -> getRealWindowWidth() != prevWindowWidth || g -> getWindow() -> getRealWindowHeight() != prevWindowHeight) {
        hud->updatePositions();
    }
}

void MenuState::Render(){

}

void MenuState::CleanUp(){

}