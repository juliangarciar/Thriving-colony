#include "WinState.h"
#include "GraphicEngine/Window.h"

WinState::WinState() : State() {

}

WinState::~WinState() {
	//CleanUp
}

void WinState::Init() {
    hud = new WinMenu();
    Window::Instance() -> setGUI();
    hud -> setHUDEvents();
}

void WinState::Input() {
	
}

void WinState::Update() {
    
}

void WinState::Render() {

}

void WinState::CleanUp() {
    delete hud;
	hud = nullptr;
    Window::Instance() -> setGUI();
}