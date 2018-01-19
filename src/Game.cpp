#include "Game.h"
#include "Human.h"
#include "IA.h"

Game* Game::pinstance = 0;

Game* Game::Instance() {
    if (pinstance == 0) {
        pinstance = new Game();
    }
    return pinstance;
}

Game::Game() {
    menu = new MenuState();
    state = menu;
    stateData = Enumeration::State::MenuState;

    window = Window::Instance();

    cursor = new Mouse();
    io = new InputManager();

    events = new EventSystem();

    window -> setEventReceiver(io);
    soundSystem = new SoundSystem();
}

Game::~Game() {
     delete menu;
     delete game;
     delete pause;
     delete cursor;
     delete io;
     delete events;
     delete soundSystem;
}

void Game::init() {
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

    state -> init();
}

void Game::input() {
    io -> endEventProcess();
    state -> input();
    io -> startEventProcess();
}

void Game::update() {
    state -> update();
}

void Game::render() {
    window -> beginScene();
    state -> render();
    window -> endScene();
}

void Game::cleanUp() {
    state -> cleanUp();
    window -> close();
}

void Game::changeState(Enumeration::State data) {
    switch (data) {
        case Enumeration::State::MenuState :
            delete pause;
            delete game;
            menu = new MenuState();
            state = menu;
            state -> init();
        break;

        case Enumeration::State::GameState :
            if (stateData == Enumeration::State::MenuState) {
                delete menu;
                game = new GameState();
                state = game;
                state -> init();
            } else {
                delete pause;
                state = game;
            }
        break;

        case Enumeration::State::PauseState :
            pause = new PauseState();
            state = pause;
            state -> init();
        break;
    }
    stateData = data;
}

Window *Game::getWindow(){
    return window;
}

InputManager *Game::getIO(){
    return io;
}

Mouse *Game::getCursor(){
    return cursor;
}

EventSystem *Game::getEvents() {
    return events;
}

MenuState *Game::getMenuState(){
	return menu;
}

GameState *Game::getGameState(){
	return game;
}