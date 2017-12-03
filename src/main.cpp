#include <iostream>
#include "Game.h"

using namespace std;

int main(){
    Game *game = Game::Instance();

    game->Init();

    while (game->getWindow()->isOpen()){
        if (game->getWindow()->isReady()){
            game->Input();
            game->Update();
            game->Render();
        }
    }

    game->CleanUp();
    
    return 0;
}
