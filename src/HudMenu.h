#ifndef HUDMENU_H
#define HUDMENU_H

#include <GUIEngine/Button.h>

/**
 * @class HudMenu
 * @brief Crea un objeto tipo HudMenu
 */
class HudMenu {
    
    public:
        /**
         * @brief Constructor
         */
        HudMenu();
        /**
         * @brief Destructor
         */
        ~HudMenu();

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
};

#endif