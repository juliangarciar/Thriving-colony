#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance() {
    if (pinstance == 0) {
        pinstance = new Game();
    }
    return pinstance;
}

Game::Game() {
    window = Window::Instance();

    menu = new MenuState();
    game = new GameState();
    pause = new PauseState();

    state = game;
    stateData = Enumeration::State::GameState;

    cursor = new Mouse();
    keyboard = new Keyboard();

    events = new EventSystem();

    soundSystem = new SoundSystem();
}

Game::~Game() {
    delete menu;
    delete game;
    delete pause;
    delete cursor;
    delete events;
    delete soundSystem;
    delete keyboard;
}

void Game::Init() {
    //Initialize the event system
    //IA Events
    events -> addEvent(Enumeration::EventType::DeployTroopsIA, IA::deployTroops);
    events -> addEvent(Enumeration::EventType::RetractTroopsIA, IA::retractTroops);
    events -> addEvent(Enumeration::EventType::OpenDoorsIA, IA::openDoors);
    events -> addEvent(Enumeration::EventType::CloseDoorsIA, IA::closeDoors);

    //Human events
    events -> addEvent(Enumeration::EventType::DeployTroopsHuman, Human::deployTroops);
    events -> addEvent(Enumeration::EventType::RetractTroopsHuman, Human::retractTroops);
    events -> addEvent(Enumeration::EventType::OpenDoorsHuman, Human::openDoors);
    events -> addEvent(Enumeration::EventType::CloseDoorsHuman, Human::closeDoors);

    //Hud events
    events -> addEvent(Enumeration::EventType::EnableText, Hud::drawWarning);
    events -> addEvent(Enumeration::EventType::DisableText, Hud::deleteWarning);

    state -> Init();
}

void Game::Input() {
    state -> Input();
    cursor->refreshStates();
}

void Game::Update() {
    state -> Update();
}

void Game::Render() {
    window -> beginScene();
    state -> Render();
    window -> endScene();
}

void Game::CleanUp() {
    state -> CleanUp();
    window -> close();
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
        case Enumeration::State::PauseState :
            state -> CleanUp();
            state = pause;
            state -> Init();
        break;
    }
    stateData = data;
}

Window *Game::getWindow(){
    return window;
}

Keyboard *Game::getKeyboard(){
    return keyboard;
}

Mouse *Game::getMouse() {
    return cursor;
}

EventSystem *Game::getEvents() {
    return events;
}

MenuState *Game::getMenuState() {
	return menu;
}

GameState *Game::getGameState() {
	return game;
}