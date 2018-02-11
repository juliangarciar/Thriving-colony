#include <iostream>
#include "Game.h"

using namespace std;

i32 main() {
    Game *game = Game::Instance();

    game -> Init();

    while (game -> getWindow() -> isOpen()){
        game -> Input();
        game -> Update();
        game -> Render();
    }

    game -> CleanUp();
    
    return 0;
}
