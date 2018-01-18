#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance() {
    if (pinstance == 0) {
        pinstance = new Game();
    }
    return pinstance;
}

Game::Game() {
    menu = new MenuState();
    state = menu;

    window = Window::Instance();

    cursor = new Mouse();
    io = new InputManager();

    events = new EventSystem();

    window -> setEventReceiver(io);
    soundSystem = new SoundSystem();
}

Game::~Game() {
     delete menu;
     delete game;
     delete cursor;
     delete io;
     delete events;
     delete soundSystem;
}

void Game::init() {
    state -> init();
}

void Game::input() {
    io -> endEventProcess();
    state -> input();
    io -> startEventProcess();
}

void Game::update() {
    state -> update();
}

void Game::render() {
    window -> beginScene();
    state -> render();
    window -> endScene();
}

void Game::cleanUp() {
    state -> cleanUp();
    window -> close();
}

void Game::changeState(Enumeration::State data) {
    switch (data) {
        case Enumeration::State::MenuState :
            delete game;
            menu = new MenuState();
            state = menu;
            state -> init();
        break;

        case Enumeration::State::GameState :
            delete menu;
            game = new GameState();
            state = game;
            state -> init();
        break;
    }
}

Window *Game::getWindow(){
    return window;
}

InputManager *Game::getIO(){
    return io;
}

Mouse *Game::getCursor(){
    return cursor;
}

EventSystem *Game::getEvents() {
    return events;
}

MenuState *Game::getMenuState(){
	return menu;
}

GameState *Game::getGameState(){
	return game;
}