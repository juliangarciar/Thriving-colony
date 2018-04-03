#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() {
    //Main
    bgMain = new Panel("Thriving colony");
    //bgMain -> setPosition(Vector2<i32>(400, 200));
    bgMain -> setSize(Vector2<i32>(400, 300));
    bgMain -> setVerticalLayout();
    bgMain -> refreshLayout();
    bgMain -> center();

    buttonStart = new Button(bgMain, "Play");
    buttonOptions = new Button(bgMain, "Options"); 
    buttonQuit = new Button(bgMain, "Quit");
    //Options
    bgOptions = new Panel("Options");
    bgOptions -> setSize(Vector2<i32>(400, 300));
    bgOptions -> setVerticalLayout();
    bgOptions -> refreshLayout();
    bgOptions -> center();

    std::vector<std::string> *languages = new std::vector<std::string>();
    std::vector<std::string> *resolution = new std::vector<std::string>();

    languages -> push_back("English");
    languages -> push_back("Spanish");

    resolution -> push_back("640x480");
    resolution -> push_back("1080x720");


    languageP = new Label(bgOptions, "Choose a language.");
    languageP -> setSize(Vector2<i32>(120, 25));

    languageCb = new ComboBox(bgOptions, *languages);
    languageCb -> setPosition(Vector2<i32>(400, 200));
    languageCb -> setSize(Vector2<i32>(120, 60));

    resolutionP = new Label(bgOptions, "Choose a screen resolution.");
    resolutionP -> setSize(Vector2<i32>(180, 25));

    resolutionCb = new ComboBox(bgOptions, *resolution);
    resolutionCb -> setPosition(Vector2<i32>(400, 200));
    resolutionCb -> setSize(Vector2<i32>(120, 60));


    languages -> clear();
    delete languages;
    resolution -> clear();
    delete resolution;//me irl
    // No va bien
    /*
    volumeSlider = new Slider(bgOptions);
    //bgOptions -> addChild(volumeSlider);
    volumeSlider -> setRange(std::pair<f32, f32>(0,100));
    volumeSlider -> setPosition(Vector2<i32>(400, 300));
*/
    buttonAccept = new Button(bgOptions, "Accept changes");
    bgOptions -> hide();
    //Play

    std::vector<std::string> *races = new std::vector<std::string>();
    std::vector<std::string> *maps = new std::vector<std::string>();

    races -> push_back("Drorania");
    races -> push_back("Kaonov");

    maps -> push_back("Grim hollow");

    bgPlay = new Panel("Match options");
    bgPlay -> setSize(Vector2<i32>(400, 300));
    bgPlay -> setVerticalLayout();
    bgPlay -> refreshLayout();
    bgPlay -> center();


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

    races -> clear();
    delete races;
    maps -> clear();
    delete maps;

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
    delete languageP;
    delete languageCb,
    delete resolutionP;
    delete resolutionCb;
    delete volumeSlider;
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