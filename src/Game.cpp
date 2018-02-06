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
    window = Window::Instance();

    menu = new MenuState();
    state = menu;
    stateData = Enumeration::State::MenuState;

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
    state -> input();
    cursor->refreshStates();
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
            IA::getInstance() -> cleanUp();
            Human::getInstance() -> cleanUp();
            delete game;
            menu = new MenuState();
            state = menu;
            state -> init();
        break;

        case Enumeration::State::GameState :
            if (stateData == Enumeration::State::MenuState) {
                delete menu;
                IA::getInstance() -> init();
                Human::getInstance() -> init();
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