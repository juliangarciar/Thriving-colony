#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <Types.h>

/**
 * @class Human.
 * @brief Create a Human type object. Public heritage from Player class. Singleton class.
 */
class Human : public Player {

    public:
        /**
         * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * 
         * @return Pointer to a Human object that will be the value of instance variable.
		 */
        static Human* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init();

        /**
         * @brief Update buildings and units variables.
         */
        void Update();

        /**
         * @brief Delete all variables.
         */
        void CleanUp();

        /**
         * @brief Determinate if the player's city is under attack.
         * 
         * @return True if there ir any enemie troop near the player's city and false in other case.
         */
        bool getUnderAttack();

    protected:
        /**
         * Human constructor.
         */
        Human();

        /**
         * HUman destructor.
         */
        virtual ~Human();

    private:
        //Pointer to the only instance of Human class.
        static Human* instance;
};

#endif
