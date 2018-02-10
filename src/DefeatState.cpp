#include "DefeatState.h"
#include "Game.h"

DefeatState::DefeatState() : State() {

}

DefeatState::~DefeatState() {

}

void DefeatState::Init() {
    hud = new DefeatMenu();
    Window::Instance() -> setGUI();
    hud -> setHUDEvents();
}

void DefeatState::Input() {
    hud -> update();
}

void DefeatState::Update() {
    
}

void DefeatState::Render() {

}

void DefeatState::CleanUp() {
    delete hud;
    Window::Instance() -> setGUI();
}