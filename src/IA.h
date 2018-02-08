#ifndef IA_H
#define IA_H

#include "Player.h"
#include "IAEngine/BehaviourTree.h"
#include "IAEngine/RootNode.h"
#include <Types.h>

/**
 * @class Hud
 * @brief Crea un objeto tipo Hud
 */
class IA : public Player {
    
    public:
        /**
         * @brief Constructor
         */
        IA();
        /**
         * @brief Destructor
         */
        virtual ~IA();
        /**
         * @brief Solicita la instancia IA
         * @return Devuelve un puntero al objeto IA
         */
        static IA* getInstance();

        /**
         * @brief Inicializa la IA
         */
        void init();
        /**
         * @brief Constructor
         */
        void cleanUp();

        /**
         * @brief Despliega las tropas
         */
        static void deployTroops();
        /**
         * @brief Retira las tropas
         */
        static void retractTroops();
        /**
         * @brief Cierra las puertas de la ciudad
         */
        static void closeDoors();
        /**
         * @brief Abre las puertas de la ciudad
         */
        static void openDoors();
        /**
         * @brief Solicita el arbol de comportamiento
         * @return behaviourTree sera el arbol devuelto
         */
        BehaviourTree* getTree();

        /**
         * @brief Determina la posicion de construccion de un edificio
         * @return position sera un vector de posicion con las coordenadas del nuevo edificio
         */
        Vector3<f32> determinatePositionBuilding();
        /**
         * @brief Actualiza la IA
         */
        virtual void update();

        /**
         * @brief Comprueba si esta siendo atacada
         * @return true en caso afirmativo y false, en caso contrario
         */
        bool getUnderAttack();
        /**
         * @brief Comprueba si las tropas estan desplegadas
         * @return true en caso afirmativo y false, en caso contrario
         */
        bool getDeployedTroops();
        /**
         * @brief Comprueba si las puertas de la ciudad estan cerradas
         * @return true en caso afirmativo y false, en caso contrario
         */
        bool getClosedDoors();

        /**
         * @brief Cambia el choiceIndex actual por el pasado por parametro
         * @param choiceIndex con el nuevo numero
         */
        void setChoiceIndex(i32);
        /**
         * @brief Solicita la proxima decision de la IA
         * @return nextChoice de tipo string 
         */
        std::string getNextChoice();
        /**
         * @brief Solicita el comportamiento elegido por la IA
         * @return chosenBehaviour de tipo string 
         */
        std::string getChosenBehaviour();
        /**
         * @brief Inicializa las posibles decisiones de la IA
         */
        void initializeChoices();

        /**
         * @brief Decide que comportamiento va a tener la IA
         */
        void chooseBehaviour();
    private:
        i32 updateTimer;

        static IA* instance;
        static bool deployedTroops;
        static bool closedDoors;
        BehaviourTree* tree;
        RootNode *nodeRootIA;

        Enumeration::IABehaviour behaviour;
        std::string chosenBehaviour;
        i32 choiceIndex;

        std::vector<std::string> * choices;

};

#endif