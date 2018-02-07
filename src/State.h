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
        virtual void Init() = 0;
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        virtual void Input() = 0;
        /**
		 * @brief Actualiza
		 */
        virtual void Update() = 0;
        /**
		 * @brief Renderiza
		 */
        virtual void Render() = 0;
        /**
		 * @brief Constructor
		 */
        virtual void CleanUp() = 0;
};

#endif

