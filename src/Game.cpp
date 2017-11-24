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
}

Game::~Game() {
    
}

void Game::Init(){
    state->Init();
}
void Game::Input(){
    state->Input();
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

Screen* Game::getWindow(){
    return window;
}