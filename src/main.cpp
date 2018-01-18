#include <iostream>
#include "Game.h"
#include "Player.h"

using namespace std;

int main() {
    Game *game = Game::Instance();

    game -> init();

    while (game -> getWindow() -> isOpen()) {
        if (game -> getWindow() -> isReady()) {
            game -> input();
            game -> update();
            game -> render();
        }
    }

    game -> cleanUp();
    
    return 0;
}
