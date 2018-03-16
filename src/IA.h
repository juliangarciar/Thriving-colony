#ifndef IA_H
#define IA_H

#include "Player.h"
#include "IAEngine/BehaviourTree.h"
#include "IAEngine/RootNode.h"
#include "AIEngine/ActiveSelector.h"
#include <Types.h>

/**
 * @class Hud
 * @brief Crea un objeto tipo Hud
 */
class IA : public Player {
    public:
        /**
         * @brief Solicita la instancia IA
         * @return Devuelve un puntero al objeto IA
         */
        static IA* Instance();

        /**
         * @brief Inicializa la IA
         */
        void Init();
        /**
         * @brief Actualiza la IA
         */
        void Update();
        /**
         * @brief Constructor
         */
        void CleanUp();

        /**
         * @brief Determina la posicion de construccion de un edificio
         * @return position sera un vector de posicion con las coordenadas del nuevo edificio
         */
        Vector3<f32> determinatePositionBuilding();

        /**
         * @brief Inicializa las posibles decisiones de la IA
         */
        void initializeChoices();

        /**
         * @brief Decide que comportamiento va a tener la IA
         */
        void chooseBehaviour();
        
        /**
         * @brief Cambia el choiceIndex actual por el pasado por parametro
         * @param choiceIndex con el nuevo numero
         */
        void setChoiceIndex(i32);

        /**
         * @brief Comprueba si esta siendo atacada
         * @return true en caso afirmativo y false, en caso contrario
         */
        bool getUnderAttack();
        
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
         * @brief Solicita el arbol de comportamiento
         * @return behaviourTree sera el arbol devuelto
         */
        BehaviourTree* getTree();

        ActiveSelector* getRootNode();
        
        bool getFast();
    protected:
        /**
         * @brief Constructor
         */
        IA();
        /**
         * @brief Destructor
         */
        virtual ~IA();
    private:
        static IA* instance;

        BehaviourTree* tree;
        RootNode *nodeRootIA;

        ActiveSelector *rootNode;

        Enumeration::IABehaviour behaviour;
        std::string chosenBehaviour;
        std::vector<std::string> *choices;
        i32 choiceIndex;

        bool fast;
};

#endif