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
    game = new GameState();
    win = new WinState();
    defeat = new DefeatState();

    state = menu;
    stateData = Enumeration::State::GameState;

    soundSystem = nullptr;
}

Game::~Game() {
    delete menu;
    delete game;
    delete win;
    delete defeat;
}

void Game::Init() {
	Window::Instance() -> Init(1280, 720);
	IO::Instance() -> Init();
    /* Cargar cursores */
    IO::Instance()->loadImageIcon("media/icons/Mouse/cursor_azul.png");
    IO::Instance()->loadImageIcon("media/icons/Mouse/cursor_verde.png");
    IO::Instance()->loadImageIcon("media/icons/Mouse/cursor_rojo.png");
    IO::Instance() -> getMouse() -> changeCustomIcon(0);
    soundSystem = SoundSystem::Instance();
    SoundSystem::Instance() -> stopMusicEvent();
    SoundSystem::Instance() -> playMusicEvent("MenuMusic");
    state -> Init();
}

void Game::Input() {
    state -> Input();
}

void Game::Update() {
    
    SoundSystem::Instance() -> update();
	IO::Instance() -> Update();
    state -> Update();
}

void Game::Render() {
    Window::Instance() -> beginScene();
    state -> Render();
    Window::Instance() -> endScene();
}

void Game::CleanUp() {
    state -> CleanUp();
    Window::Instance() -> close();
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

MenuState *Game::getMenuState() {
	return menu;
}

GameState *Game::getGameState() {
	return game;
}