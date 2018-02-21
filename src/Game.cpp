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

    io = IO::Instance();

    menu = new MenuState();
    game = new GameState();
    win = new WinState();
    defeat = new DefeatState();

    state = menu;
    stateData = Enumeration::State::GameState;

    soundSystem = SoundSystem::Instance();
}

Game::~Game() {
    //delete window;

    //delete io;

    delete menu;
    delete game;
    delete win;
    delete defeat;

    delete soundSystem;
}

void Game::Init() {
    state -> Init();
}

void Game::Input() {
    state -> Input();
    io->getMouse()->refreshStates();
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

MenuState *Game::getMenuState() {
	return menu;
}

GameState *Game::getGameState() {
	return game;
}