#include "MenuState.h"
#include "GraphicEngine/Window.h"

MenuState::MenuState() : State() {
    
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
    
}

void MenuState::Render() {

}

void MenuState::CleanUp() {
    delete hud;
    Window::Instance() -> setGUI();
}