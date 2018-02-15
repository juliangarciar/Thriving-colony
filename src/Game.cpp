#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance() {
    if (pinstance == 0) {
        pinstance = new Game();
    }
    return pinstance;
}

Game::Game() {
    window = Window::Instance();

    menu = new MenuState();
    game = new GameState();
    win = new WinState();
    defeat = new DefeatState();

    state = menu;
    stateData = Enumeration::State::GameState;

    cursor = new Mouse();
    keyboard = new Keyboard();

    events = new EventSystem();

    soundSystem = SoundSystem::Instance(); 

    resourceManager = new ResourceManager();
}

Game::~Game() {
    delete menu;
    delete game;
    delete win;
    delete defeat;

    delete cursor;
    delete keyboard;
    
    delete events;
    delete soundSystem;
}

void Game::Init() {
    state -> Init();
}

void Game::Input() {
    state -> Input();
    cursor->refreshStates();
}

void Game::Update() {
    state -> Update();
}

void Game::Render() {
    window -> beginScene();
    state -> Render();
    window -> endScene();
}

void Game::CleanUp() {
    state -> CleanUp();
    window -> close();
}

void Game::changeState(Enumeration::State data) {
    switch (data) {
        case Enumeration::State::MenuState:
            state -> CleanUp();
            state = menu;
            state -> Init();
        break;
        case Enumeration::State::GameState:
            state -> CleanUp();
            state = game;
            state -> Init();
        break;
        case Enumeration::State::WinState:
            state -> CleanUp();
            state = win;
            state -> Init();
        break;
        case Enumeration::State::DefeatState:
            state -> CleanUp();
            state = defeat;
            state -> Init();
        break;
    }
    stateData = data;
}

Window *Game::getWindow(){
    return window;
}

Keyboard *Game::getKeyboard(){
    return keyboard;
}

Mouse *Game::getMouse() {
    return cursor;
}

EventSystem *Game::getEventManager() {
    return events;
}

MenuState *Game::getMenuState() {
	return menu;
}

GameState *Game::getGameState() {
	return game;
}

ResourceManager *Game::getResourceManager(){
    return resourceManager;
}