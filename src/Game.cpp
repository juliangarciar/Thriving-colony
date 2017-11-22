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
}

Game::~Game() {
    
}