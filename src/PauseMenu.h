#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <GUIEngine/Button.h>
#include <Types.h>
#include <GUIEngine/Panel.h>

/**
 * @class PauseMenu.
 * @brief Create a PauseMenu type object.
 */
class PauseMenu {
    
    public:
        /**
         * @brief PauseMenu constructor.
         */
        PauseMenu();

        /**
         * @brief PauseMenu destructor
         */
        ~PauseMenu();

        /**
         * @brief Set the different events associated to each PauseMenu buttons. 
         */
        void setHUDEvents();

        /**
         * @brief Update.
         */
        void update();

    private:
        //POinter to Button object that closes the game.
        Button *buttonQuit;

        //Pointer to Button object that resumes the game.
        Button *buttonResume;

        //Pointer to Button object that goes to the main menu.
        Button *buttonMenu;

        //Panel where all buttons are shown.
        Panel* bgMenu;
};

#endif