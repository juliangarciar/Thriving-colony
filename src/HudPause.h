#ifndef HUDPAUSE_H
#define HUDPAUSE_H

#include <GUIEngine/Button.h>

/**
 * @class HudPause
 * @brief Crea un objeto tipo HudPause
 */
class HudPause {
    
    public:
        /**
         * @brief Constructor
         */
        HudPause();
        /**
         * @brief Destructor
         */
        ~HudPause();

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
        Button *buttonResume;
        Button *buttonMenu;
};

#endif