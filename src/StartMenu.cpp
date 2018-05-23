#include "StartMenu.h"
#include "Game.h"
#include <SoundEngine/SoundSystem.h>

StartMenu::StartMenu() {
#ifdef USEVIDEO
	video = new Video("media/videos/Pantalla_menu.mp4");
	video -> play();
	video -> setLoop(true);
#endif
    //SoundSystem::Instance() -> playMusicEvent("MenuMusic");
    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource("media/maps/maplist.json", true);
    json j = *r -> getJSON();

    //Main
    bgMain = new Panel("Thriving colony");
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

    languages . push_back("English");
    languages . push_back("Spanish");

    resolution . push_back("640x480");
    resolution . push_back("1280x720");

    languageP = new Label(bgOptions, "Choose a language.");
    languageP -> setSize(Vector2<i32>(120, 25));

    languageCb = new ComboBox(bgOptions, languages);
    languageCb -> setPosition(Vector2<i32>(400, 200));
    languageCb -> setSize(Vector2<i32>(120, 60));

    resolutionP = new Label(bgOptions, "Choose a screen resolution.");
    resolutionP -> setSize(Vector2<i32>(180, 25));

    resolutionCb = new ComboBox(bgOptions, resolution);
    resolutionCb -> setPosition(Vector2<i32>(400, 200));
    resolutionCb -> setSize(Vector2<i32>(120, 60));
    
    buttonAccept = new Button(bgOptions, "Accept changes");
    bgOptions -> hide();

    //Play
    races . push_back("Drorania");
    races . push_back("Kaonov");

    for (auto& element : j["list"]) {
    	maps . push_back(element["name"].get<std::string>());
    	map_paths . push_back(element["map"].get<std::string>());
	}

    bgPlay = new Panel("Match options");
    bgPlay -> setSize(Vector2<i32>(400, 300));
    bgPlay -> setVerticalLayout();
    bgPlay -> refreshLayout();
    bgPlay -> center();

    racesP = new Label(bgPlay, "Select a race.");
    racesP -> setSize(Vector2<i32>(120, 25));

    racesCb = new ComboBox(bgPlay, races);
    racesCb -> setPosition(Vector2<i32>(400, 200));
    racesCb -> setSize(Vector2<i32>(120, 60));

    mapsP = new Label(bgPlay, "Select a map.");
    mapsP -> setSize(Vector2<i32>(120, 25));

    mapsCb = new ComboBox(bgPlay, maps);
    mapsCb -> setPosition(Vector2<i32>(400, 200));
    mapsCb -> setSize(Vector2<i32>(120, 60));

    buttonPlay = new Button(bgPlay, "Start match");
    buttonBack = new Button(bgPlay, "Main menu"); 
    bgPlay -> hide();

    Window::Instance() -> setGUI();

	Game::Instance() -> getGameState() -> getMap() -> setMap(map_paths[mapsCb->getSelectedOption()]);
	if (races[racesCb->getSelectedOption()] == "Drorania") Game::Instance() -> getGameState() -> getMap() -> setBreeds("Drorania", "Kaonov");
	else if (races[racesCb->getSelectedOption()] == "Kaonov") Game::Instance() -> getGameState() -> getMap() -> setBreeds("Kaonov", "Drorania");
}

StartMenu::~StartMenu() {
    races . clear();
    maps . clear();
    languages . clear();
    resolution . clear();

    delete buttonQuit;
    delete buttonStart;
    delete buttonOptions;
    delete bgMain;

    delete bgOptions;
    delete languageP;
    delete languageCb,
    delete resolutionP;
    delete resolutionCb;
    delete buttonAccept;

    delete bgPlay;
    delete racesP;
    delete racesCb;
    delete mapsP;
    delete mapsCb;
    delete buttonPlay;
    delete buttonBack;
#ifdef USEVIDEO
	delete video;
#endif
}

void StartMenu::setHUDEvents() {
    buttonQuit -> setCallback([]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        Window::Instance() -> close();
    });

    buttonStart -> setCallback([this]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        bgMain -> hide();
        bgPlay -> show();
    });

    buttonOptions -> setCallback([this]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        bgMain -> hide();
        bgOptions -> show();
    });

    buttonAccept -> setCallback([this]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        bgOptions -> hide();
        bgMain -> show();
    });

	mapsCb -> setCallback([this] (bool a) {
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
		Game::Instance() -> getGameState() -> getMap() -> setMap(map_paths[mapsCb->getSelectedOption()]);
    });

	racesCb -> setCallback([this] (bool a) {
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
		if (races[racesCb->getSelectedOption()] == "Drorania") Game::Instance() -> getGameState() -> getMap() -> setBreeds("Drorania", "Kaonov");
		else if (races[racesCb->getSelectedOption()] == "Kaonov") Game::Instance() -> getGameState() -> getMap() -> setBreeds("Kaonov", "Drorania");
    });

    buttonPlay -> setCallback([]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        Game::Instance() -> changeState(Enumeration::State::GameState);
    });

    buttonBack -> setCallback([this]{
        SoundSystem::Instance() -> playSFXEvent("MenuClick");
        bgMain -> show();
        bgPlay -> hide();
    });

}