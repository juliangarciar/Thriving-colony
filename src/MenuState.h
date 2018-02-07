#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StartMenu.h"

/**
 * @class MenuState
 * @brief Tiene herencia publica de state y crea un objeto tipo MenuState
 */
class MenuState : public State {
    
public:
        /**
         * @brief Constructor
         */
        MenuState();
        /**
         * @brief Constructor
         */
        virtual ~MenuState();

        /**
         * @brief Inicializa MenuState
         */
        void Init();
        /**
         * @brief Recoge las entradas de teclado y raton
         */
        void Input();
        /**
         * @brief Actualiza
         */
        void Update();
        /**
         * @brief Renderiza
         */
        void Render();
        /**
         * @brief Constructor
         */
        void CleanUp();

    private:
        StartMenu *hud;

        int prevWindowWidth;
        int prevWindowHeight;
};

#endif