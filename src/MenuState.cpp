#include "MenuState.h"
#include "GraphicEngine/Window.h"

MenuState::MenuState() : State() {
    
}

MenuState::~MenuState() {
	//CleanUp
}

void MenuState::Init() {
    hud = new StartMenu();
    Window::Instance() -> setGUI();
    
    hud -> setHUDEvents();
}

void MenuState::Input() {
	
}

void MenuState::Update() {
    
}

void MenuState::Render() {

}

void MenuState::CleanUp() {
    delete hud;
	hud = nullptr;
    Window::Instance() -> setGUI();
}