#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StartMenu.h"
#include <Types.h>

/**
 * @class MenuState.
 * @brief Create a MenuState type object. Public heritage from State class.
 */
class MenuState : public State {
    
public:
        /**
         * @brief MenuState constructor.
         */
        MenuState();

        /**
         * @brief MenuState destructor.
         */
        virtual ~MenuState();

        /**
         * @brief Initialize the variables.
         */
        void Init();

        /**
         * @brief Update the hud variable.
         * @see update() method of StartMenu class.
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
        StartMenu *hud;
};

#endif