#include <iostream>
#include "Game.h"
#include "Player.h"

using namespace std;

int main(){
    Game *game = Game::Instance();

    game->Init();

    while (game->getWindow()->isOpen()){
        game->Input();
        game->Update();
        game->Render();
    }

    game->CleanUp();
    
    return 0;
}
