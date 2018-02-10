#ifndef DEFEATMENU_H
#define DEFEATMENU_H

#include <GUIEngine/Button.h>
#include <GUIEngine/Label.h>

/**
 * @class DefeatMenu
 * @brief Crea un objeto tipo DefeatMenu
 */
class DefeatMenu {
    
    public:
        /**
         * @brief Constructor
         */
        DefeatMenu();
        /**
         * @brief Destructor
         */
        ~DefeatMenu();

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