#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() {
    //Main
    bgMain = new Panel("Thriving colony");
    bgMain -> setPosition(Vector2<i32>(400, 200));
    bgMain -> setSize(Vector2<i32>(400, 300));
    bgMain -> setVerticalLayout();

    buttonStart = new Button(bgMain, "Play");
    buttonOptions = new Button(bgMain, "Options"); 
    buttonQuit = new Button(bgMain, "Quit");
    //Options
    bgOptions = new Panel("Options");
    bgOptions -> setPosition(Vector2<i32>(400, 200));
    bgOptions -> setSize(Vector2<i32>(400, 300));
    bgOptions -> setVerticalLayout();

    buttonAccept = new Button(bgOptions, "Accept changes");

    bgOptions -> hide();
    //Play

    std::vector<std::string> *races = new std::vector<std::string>();
    std::vector<std::string> *maps = new std::vector<std::string>();

    races -> push_back("Drorania");
    races -> push_back("Kaonov");

    maps -> push_back("Grim hollow");

    bgPlay = new Panel("Match options");
    bgPlay -> setPosition(Vector2<i32>(400, 200));
    bgPlay -> setSize(Vector2<i32>(400, 300));
    bgPlay -> setVerticalLayout();

    racesP = new Label(bgPlay, "Select a race.");
    racesP -> setSize(Vector2<i32>(120, 25));

    racesCb = new ComboBox(bgPlay, *races);
    racesCb -> setPosition(Vector2<i32>(400, 200));
    racesCb -> setSize(Vector2<i32>(120, 60));

    mapsP = new Label(bgPlay, "Select a map.");
    mapsP -> setSize(Vector2<i32>(120, 25));

    mapsCb = new ComboBox(bgPlay, *maps);
    mapsCb -> setPosition(Vector2<i32>(400, 200));
    mapsCb -> setSize(Vector2<i32>(120, 60));

    buttonPlay = new Button(bgPlay, "Start match");
    buttonBack = new Button(bgPlay, "Main menu"); 
    bgPlay -> hide();


    Window::Instance() -> setGUI();   

}

StartMenu::~StartMenu() {
    delete bgMain;
    delete buttonQuit;
    delete buttonStart;
    delete bgOptions;
    delete buttonAccept;

    delete bgPlay;
    delete racesP;
    delete racesCb;
    delete mapsP;
    delete mapsCb;
    delete buttonPlay;
    delete buttonBack;

}

void StartMenu::setHUDEvents(){
    buttonQuit -> setCallback([]{
        Window::Instance() -> close();
    });

    buttonStart -> setCallback([this]{
        bgMain -> hide();
        bgPlay -> show();
    });

    buttonOptions -> setCallback([this]{
        bgMain -> hide();
        bgOptions -> show();
    });

    buttonAccept -> setCallback([this]{
        bgOptions -> hide();
        bgMain -> show();
    });

    buttonPlay -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::GameState);
    });

    buttonBack -> setCallback([this]{
        bgMain -> show();
        bgPlay -> hide();
    });

}

void StartMenu::update() {

}