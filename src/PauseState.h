#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "PauseMenu.h"

/**
 * @class PauseState
 * @brief Tiene herencia publica de State y crea un objeto tipo PauseState
 */
class PauseState : public State {
    
    public:
        /**
		 * @brief Constructor
		 */
        PauseState();
        /**
		 * @brief Destructor
		 */
        virtual ~PauseState();

        /**
		 * @brief Inicializa
		 */
        void init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void input();
        /**
		 * @brief Actualiza
		 */
        void update();
        /**
		 * @brief Renderiza
		 */
        void render();
        /**
		 * @brief Constructor
		 */
        void cleanUp();

    private:
        PauseMenu *hud;

        int prevWindowWidth;
        int prevWindowHeight;
};

#endif