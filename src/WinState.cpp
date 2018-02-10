#include "WinState.h"
#include "Game.h"

WinState::WinState() : State() {

}

WinState::~WinState() {

}

void WinState::Init() {
    hud = new WinMenu();
    Window::Instance() -> setGUI();
    hud -> setHUDEvents();
}

void WinState::Input() {
    hud -> update();
}

void WinState::Update() {
    
}

void WinState::Render() {

}

void WinState::CleanUp() {
    delete hud;
    Window::Instance() -> setGUI();
}