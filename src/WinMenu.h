#ifndef WINMENU_H
#define WINMENU_H

#include <GUIEngine/Button.h>
#include <GUIEngine/Label.h>

/**
 * @class WinMenu
 * @brief Crea un objeto tipo WinMenu
 */
class WinMenu {
    
    public:
        /**
         * @brief Constructor
         */
        WinMenu();
        /**
         * @brief Destructor
         */
        ~WinMenu();

        /**
         * @brief Establece los distintos eventos asociados a cada uno de los botones del HUD 
         */
        void setHUDEvents();

        /**
         * @brief Actualiza el HUD
         */
        void update();

    private:
        Button *buttonQuit;
        Button *buttonStart;

        Label *winText;
};

#endif