#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"
#include "WinMenu.h"

/**
 * @class WinState.
 * @brief Create a WinState type object. Public heritage from State class.
 */
class WinState : public State {
    
    public:
        /**
         * @brief WinState constructor.
         */
        WinState();

        /**
         * @brief WinState destructor.
         */
        virtual ~WinState();

        /**
         * @brief Initialize the variables.
         */
        void Init();

        /**
         * @brief Update the hud variable.
         * 
         * @see update() method of WinMenu class.
         */
        void Input();

        /**
         * @brief Update.
         */
        void Update();

        /**
         * @brief Render.
         */
        void Render();

        /**
         * @brief Delete all variables.
         */
        void CleanUp();

    private:
        //Pointer to the hud that will be used.
        WinMenu *hud;
};

#endif