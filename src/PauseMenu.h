#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <GUIEngine/Button.h>

/**
 * @class PauseMenu
 * @brief Crea un objeto tipo PauseMenu
 */
class PauseMenu {
    
    public:
        /**
         * @brief Constructor
         */
        PauseMenu();
        /**
         * @brief Destructor
         */
        ~PauseMenu();

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