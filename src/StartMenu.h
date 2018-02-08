#ifndef STARTMENU_H
#define STARTMENU_H

#include <GUIEngine/Button.h>
#include <Types.h>

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
        Button *buttonQuit;
        Button *buttonStart;
};

#endif