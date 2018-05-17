#include "DefeatState.h"
#include "GraphicEngine/Window.h"

DefeatState::DefeatState() : State() {

}

DefeatState::~DefeatState() {
    //CleanUp
}

void DefeatState::Init() {
    hud = new DefeatMenu();
    Window::Instance() -> setGUI();
    hud -> setHUDEvents();
}

void DefeatState::Input() {
	
}

void DefeatState::Update() {
    
}

void DefeatState::Render() {

}

void DefeatState::CleanUp() {
    delete hud;
	hud = nullptr;
    Window::Instance() -> setGUI();
}