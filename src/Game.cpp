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
    win = new WinState();
    defeat = new DefeatState();

    state = game;
    stateData = Enumeration::State::GameState;

    cursor = new Mouse();
    keyboard = new Keyboard();

    events = new EventSystem();

    Window::Instance() -> setGUI();
// Added by Julian
    Graph::Instance();
    cellSpace = new CellSpacePartition(10240, 10240, 128, 128, 4);
    soundSystem = SoundSystem::Instance();
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
    events -> addEvent(Enumeration::EventType::RetractTroopsIA, []() {
        IA::Instance()->getUnitManager()->retractAllTroops();
    });
    /*events -> addEvent(Enumeration::EventType::DeployAllTroopsIA, []() {
        IA::Instance()->getUnitManager()->deployAllTroops();
    });*/

    //Human events
    events -> addEvent(Enumeration::EventType::RetractTroopsHuman, []() {
        Human::Instance()->getUnitManager()->retractAllTroops();
    });
    /*events -> addEvent(Enumeration::EventType::DeployAllTroopsHuman, []() {
        Human::Instance()->getUnitManager()->deployAllTroops();
    });*/

    //Hud events
    //events -> addEvent(Enumeration::EventType::EnableText, Hud::drawWarning);
    //events -> addEvent(Enumeration::EventType::DisableText, Hud::deleteWarning);

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
        case Enumeration::State::PauseState:
            //ToDo: de momento lo dejo asi para que pueda ser un estado pero el menu es parte del gamestate
            //state -> CleanUp();
            state = pause;
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

CellSpacePartition *Game::getCellSpace(){
    return cellSpace;
}