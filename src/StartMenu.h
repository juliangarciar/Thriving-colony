#ifndef STARTMENU_H
#define STARTMENU_H

#include <GUIEngine/Button.h>
#include <Types.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/ComboBox.h>
#include <GUIEngine/Label.h>
/**
 * @class StartMenu
 * @brief Crea un objeto tipo StartMenu
 */
class StartMenu {
    
    public:
        /**
         * @brief Constructor
         */
        StartMenu();
        /**
         * @brief Destructor
         */
        ~StartMenu();

        /**
         * @brief Establece los distintos eventos asociados a cada uno de los botones del HUD 
         */
        void setHUDEvents();

        /**
         * @brief Actualiza el HUD
         */
        void update();

    private:
        //MainMenu
        Button *buttonQuit;
        Button *buttonOptions;
        Button *buttonStart;
        Panel *bgMain;

        //OptionsMenu
        Panel *bgOptions;
        Button *buttonAccept;
        
        //PlayMenu
        Panel *bgPlay;
        Label *racesP;
        ComboBox *racesCb;
        Label *mapsP;
        ComboBox *mapsCb;
        Button *buttonPlay;
        Button *buttonBack;

};

#endif