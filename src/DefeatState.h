#ifndef DEFEATSTATE_H
#define DEFEATSTATE_H

#include "State.h"
#include "DefeatMenu.h"

/**
 * @class DefeatState.
 * @brief Create a DefeatState type object. Public heritage from State class.
 */
class DefeatState : public State {
    
    public:
        /**
         * @brief DefeatState constructor.
         */
        DefeatState();

        /**
         * @brief DefeatState destructor.
         */
        virtual ~DefeatState();

        /**
         * @brief Initialize the variables.
         */
        void Init();

        /**
         * @brief Update the hud variable.
         * 
         * @see update() method of DefeatMenu class.
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
        DefeatMenu *hud;
};

#endif