#ifndef STARTMENU_H
#define STARTMENU_H

#include <Types.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/ComboBox.h>
#include <GUIEngine/Label.h>
#include <GUIEngine/Slider.h>
#include <GraphicEngine/Video.h>

/**
 * @class StartMenu.
 * @brief Create a StartMenu type object.
 */
class StartMenu {
    
    public:
        /**
         * @brief StartMenu constructor.
         */
        StartMenu();
        
        /**
         * @brief StartMenu destructor.
         */
        ~StartMenu();

        /**
         * @brief Set the different events associated to each StartMenu button. 
         */
        void setHUDEvents();

    private:
        //Pointer to Button object that closes the game.
        Button *buttonQuit;

        //Pointer to Button object that goes to the game options.
        Button *buttonOptions;

        //Pointer to Button object that starts the game.
        Button *buttonStart;

        //Panel where are going to be shown the main menu buttons.
        Panel *bgMain;

        //Panel where are going to be shown the options menu buttons.
        Panel *bgOptions;

        //Text of the language of the game.
        Label *languageP;

        //List of available languages for the game.
        ComboBox *languageCb;

        //Text of the resolution of the game.
        Label *resolutionP;

        //List of available resolutions for the game.
        ComboBox *resolutionCb;

        //Pointer to Button object that accept the selected options.
        Button *buttonAccept;
        
        //Panel where are going to be shown the options for the game.
        Panel *bgPlay;

        //Text of the civilization for the human player.
        Label *racesP;

        //List of available civilizations.
        ComboBox *racesCb;

        //Text of the map for the game.
        Label *mapsP;

        //List of available maps.
        ComboBox *mapsCb;

        //Pointer to Button object that starts the game.
        Button *buttonPlay;

        //Pointer to Button object that goes to the main menu.
        Button *buttonBack;

		//
#ifdef USEVIDEO
		Video *video;
#endif
};

#endif