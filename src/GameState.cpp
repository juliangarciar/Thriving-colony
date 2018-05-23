#include "GameState.h"
#include "Game.h"

GameState::GameState() : State() {
    map = Map::Instance();

    gamePaused = false;
}

GameState::~GameState() {
    //Clean Up
} 

void GameState::Init() {
    //Load map
    map -> Init();

    //Init SoundSystem
    SoundSystem::Instance() -> initSystem();
}

void GameState::Input() {
    if (gamePaused ==  false) {
        if (!Hud::Instance() -> getPopUpOpen()) {
            map -> Input();

            if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_ESCAPE)) { //ToDo: fachada
                // Si el popup esta abierto, cierralo (ToDo: no funca)
                if (Hud::Instance() -> getPopUpOpen())
                    Hud::Instance() -> hidePopup();
                // Si no, pausa el juego
                else {
                    IO::Instance() -> getMouse() -> changeCustomIcon(0);
                    pauseMenu = new PauseMenu();
                    Window::Instance() -> setGUI();
                    pauseMenu -> setHUDEvents();
                    gamePaused = true;
                }
            }
        } else {
            IO::Instance() -> getMouse() -> changeCustomIcon(0);
        }
    } else {
        pauseMenu -> update();
    }
}

void GameState::Update() {
    if (gamePaused == false) {
        //Update map
        map -> Update();

        //ToDo: NEW SOUND SYSTEM
        SoundSystem::Instance() -> playMusicEvent("event:/Music/DroraniaMusic");
        SoundSystem::Instance() -> update();

		//Resize trigger
        Window::Instance()->setResizeCallback([&](i32 newWidth, i32 newHeight) {
			//std::cout << "Resized to (" << newWidth << "," << newHeight << ")" << std::endl;
		});
    }
    //fps count goes after game logic to see how long it took to go through the logic
    Window::Instance() -> calculateFramerate();
}

void GameState::Render() {

}

void GameState::CleanUp() {
    delete pauseMenu;

    map -> CleanUp();
}

void GameState::cleanGamePaused() {
    gamePaused = false;
    delete pauseMenu;
}

Map *GameState::getMap(){
	return map;
}