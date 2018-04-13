#ifndef DEFEATMENU_H
#define DEFEATMENU_H

#include <GUIEngine/Button.h>
#include <GUIEngine/Label.h>

/**
 * @class DefeatMenu.
 * @brief Create a DefeatMenu type object.
 */
class DefeatMenu {
    
    public:
        /**
         * @brief DefeatMenu constructor.
         */
        DefeatMenu();

        /**
         * @brief DefeatMenu destructor.
         */
        ~DefeatMenu();

        /**
         * @brief Set the different events associated to each Hud button. 
         */
        void setHUDEvents();

        /**
         * @brief Update.
         */
        void update();

    private:
        //Pointer to Button object that closes the game.
        Button *buttonQuit;

        //Pointer to Button object that goes to the main menu.
        Button *buttonStart;

        //Text with the defeat message.
        Label *winText;
};

#endif