#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance() {
    if(pinstance == 0) {
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::Game() {
    window = Window::Instance();

    menu = new MenuState();
    game = new GameState();
    state = game; //ToDo: cambiar por menu

    cursor = new Mouse();
    keyboard = new Keyboard();

    events = new EventSystem();

    soundSystem = new SoundSystem();
}

Game::~Game() {
    delete menu;
    delete game;

    delete cursor;
    delete keyboard;

    delete events;

    delete soundSystem;
}

void Game::Init(){
    state -> Init();
}

void Game::Input(){
    state -> Input();
    cursor -> refreshStates();
}

void Game::Update(){
    state -> Update();
}

void Game::Render(){
    window -> beginScene();
    state -> Render();
    window -> endScene();
}

void Game::CleanUp(){
    state -> CleanUp();
    window -> onClose();
}

Window *Game::getWindow() {
    return window;
}

Keyboard *Game::getKeyboard(){
    return keyboard;
}

Mouse *Game::getCursor() {
    return cursor;
}

EventSystem *Game::getEvents() {
    return events;
}

MenuState *Game::getMenuState() {
	return menu;
}

GameState *Game::getGameState() {
	return game;
}
