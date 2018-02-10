#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"
#include "WinMenu.h"

/**
 * @class WinState
 * @brief Tiene herencia publica de state y crea un objeto tipo WinState
 */
class WinState : public State {
    
public:
        /**
         * @brief Constructor
         */
        WinState();
        /**
         * @brief Constructor
         */
        virtual ~WinState();

        /**
         * @brief Inicializa WinState
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
        WinMenu *hud;
};

#endif