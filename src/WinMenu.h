#ifndef WINMENU_H
#define WINMENU_H

#include <GUIEngine/Button.h>
#include <GUIEngine/Label.h>

/**
 * @class WinMenu.
 * @brief Create a WinMenu type object.
 */
class WinMenu {
    
    public:
        /**
         * @brief WinMenu constructor.
         */
        WinMenu();

        /**
         * @brief WinMenu destructor.
         */
        ~WinMenu();

        /**
         * @brief Set the different events associated to each Hud button. 
         */
        void setHUDEvents();

    private:
        //Pointer to Button object that closes the game.
        Button *buttonQuit;

        //Pointer to Button object that goes to the main menu.
        Button *buttonStart;

        //Text with the win message.
        Label *winText;
};

#endif