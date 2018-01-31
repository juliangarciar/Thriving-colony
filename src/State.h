#ifndef STATE_H
#define STATE_H

/**
 * @class State
 * @brief Crea un objeto tipo State
 */
class State {
    public:
        /**
		 * @brief Inicializa
		 */
        virtual void init() = 0;
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        virtual void input() = 0;
        /**
		 * @brief Actualiza
		 */
        virtual void update() = 0;
        /**
		 * @brief Renderiza
		 */
        virtual void render() = 0;
        /**
		 * @brief Constructor
		 */
        virtual void cleanUp() = 0;
};

#endif

