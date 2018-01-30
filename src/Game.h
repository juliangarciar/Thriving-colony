#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "IOEngine/EventSystem.h"

#include <IOEngine/Mouse.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/EventSystem.h>
#include <GraphicEngine/Window.h>

#include <SoundEngine/SoundSystem.h>

/**
 * @class Game
 * @brief Crea un objeto singleton tipo Game
 */
class Game {
    public:
        /**
		 * @brief Crea una Instancia de Game
		 */
        static Game* Instance();

        /**
		 * @brief Inicializa Game
		 */
        void init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void input();
        /**
		 * @brief Actualiza Game
		 */
        void update();
        /**
		 * @brief Renderiza Game
		 */
        void render();
        /**
		 * @brief Constructor
		 */
        void cleanUp();
        /**
        * @brief Cambia el estado de Game
        * @param State es el nuevo estado 
        */
        void changeState(Enumeration::State);

        /**
		 * @brief Devuelve la ventana actual
         * @return Devuelve un objeto tipo Window
		 */
        Window *getWindow();
         /**
		 * @brief Devuelve la tecla actual
         * @return Devuelve un objeto tipo Keyboard
		 */
        Keyboard *getKeyboard();
         /**
		 * @brief Devuelve las coordenadas del raton
         * @return Devuelve un objeto tipo getCursor
		 */
        Mouse *getCursor();
         /**
		 * @brief Devuelve el evento actual
         * @return Devuelve un objeto tipo EventSystem
		 */
        EventSystem *getEvents();
        /**
		 * @brief Devuelve el menu actual
         * @return Devuelve un objeto tipo MenuState
		 */
        MenuState *getMenuState();
         /**
		 * @brief Devuelve el estado de juego actual
         * @return Devuelve un objeto tipo GameState
		 */
		GameState *getGameState();
        
    protected:
        /**
		 * @brief Constructor de Game.
		 */
        Game();
        /**
		 * @brief Destructor.
		 */
        virtual ~Game();
        /**
		 * @brief Contructor. Copia una instancia nueva en Game
         * @param Game es la nueva instancia
         * @return devuelve la nueva instancia de tipo Game
		 */
        Game(const Game & );
        /**
		 * @brief Redefine el operador igual
		 */
        Game &operator = (const Game & );

    private:
        static Game* pinstance;

        State *state;
        Window *window;
        Enumeration::State stateData;

        MenuState *menu;
        GameState *game;
        PauseState *pause;

        Mouse *cursor;
        Keyboard *keyboard;

        EventSystem *events;
        
        SoundSystem *soundSystem;
};

#endif