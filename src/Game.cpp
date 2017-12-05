#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance(){
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::Game() {
    menu = new MenuState();
    game = new GameState();
    state = game; //ToDo: cambiar por menu

    window = Screen::Instance();

    cursor = new Mouse();
    io = new InputManager();

    events = new EventSystem();

    window->setEventReceiver(io);
}

Game::~Game() {
     
}

void Game::Init(){
    state->Init();
}
void Game::Input(){
    io->endEventProcess();
    state->Input();
    io->startEventProcess();
}
void Game::Update(){
    state->Update();
}
void Game::Render(){
    window->beginScene();
    state->Render();
    window->endScene();
}
void Game::CleanUp(){
    state->CleanUp();
    window->close();
}

Screen *Game::getWindow(){
    return window;
}

InputManager *Game::getIO(){
    return io;
}

Mouse *Game::getCursor(){
    return cursor;
}

Event *Game::getEvents() {
    return events;
}