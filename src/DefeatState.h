#ifndef DEFEATSTATE_H
#define DEFEATSTATE_H

#include "State.h"
#include "DefeatMenu.h"

/**
 * @class DefeatState
 * @brief Tiene herencia publica de state y crea un objeto tipo DefeatState
 */
class DefeatState : public State {
    
public:
        /**
         * @brief Constructor
         */
        DefeatState();
        /**
         * @brief Constructor
         */
        virtual ~DefeatState();

        /**
         * @brief Inicializa DefeatState
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
        DefeatMenu *hud;
};

#endif