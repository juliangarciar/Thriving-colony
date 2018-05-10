#ifndef IA_H
#define IA_H

#include "Player.h"
#include "AIEngine/BehaviourTree.h"
#include "AIEngine/ActiveSelector.h"
#include <Types.h>

/**
 * @class IA.
 * @brief Create a IA type object. Public heritage from Player class. Singleton class.
 */
class IA : public Player {
    
    public:
        /**
         * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * 
         * @return Pointer to a IA object that will be the value of instance variable.
		 */
        static IA* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init(std::string _race);

        /**
         * @brief Update buildings, units variables and choice the next step when is time.
         */
        void Update();
        
        /**
         * @brief Delete all variables.
         */
        void CleanUp();

        /**
         * @brief Deteerminate the position where will be built the next building.
         * 
         * @return Vector2 that will be the position where the next uilding wiil be built.
         */
        Vector2<f32> determinatePositionBuilding();

        /**
         * @brief Initialize all choices that can do the AI player.
         */
        void initializeChoices();

        /**
         * @brief Choose the behaviour that is going to have the AI.
         */
        void chooseBehaviour();
        
        /**
         * @brief Set choiceIndex variable as the value passed by parameter.
         * 
         * @param i32 is the value that is going to be set to choiceIndex variable.
         */
        void setChoiceIndex(i32);

        /**
         * @brief Determinate if the AI's city is under attack.
         * 
         * @return True if there ir any enemie troop near the AI's city and false in other case.
         */
        bool getUnderAttack();
        
        /**
         * @brief Get the next choice of the AI.
         * 
         * @return std::string that will be the value of choices variable at choiceIndex position.
         */
        std::string getNextChoice();

        /**
         * @brief Get the choosen beahviour of the AI.
         * 
         * @return std::string that will be the value of chosenBehaviour variable.
         */
        std::string getChosenBehaviour();

        /**
         * @brief Get the beahaviour tree of the AI.
         * 
         * @return Pointer to a BehaviourTree object that will be the value of tree variable.
         */
        BehaviourTree* getTree();

        /**
         * @brief Get the behaviour trre of the AI.
         * 
         * @return Pointer to a ActiveSelector that will be the value of rootNode variable.
         */
        ActiveSelector* getRootNode();
        
        /**
         * @brief Get the speed at which is going to be update the next choose of the AI.
         * 
         * @return True if it updates fast and false in other case.
         */
        bool getFast();

        /**
         * @brief Create a very happy behaviour tree for the AI.
         */
        void veryHappyBehaviour();

        /**
         * @brief Create a happy behaviour tree for the AI.
         */
        void happyBehaviour();

        /**
         * @brief Create a neutral behaviour tree for the AI.
         */
        void neutralBehaviour();

        /**
         * @brief Create a unhappy behaviour tree for the AI.
         */
        void unhappyBehaviour();

        /**
         * @brief Create a very unhappy behaviour tree for the AI.
         */
        void veryUnhappyBehaviour();

    protected:
        /**
         * @brief IA constructor.
         */
        IA();

        /**
         * @brief IA destructor.
         */
        virtual ~IA();

    private:
        //Pointer to the only instance of IA class.
        static IA* instance;

        //Pointer to the root of the behaviour tree.
        BehaviourTree* tree;

        //Pointer to the root of the behaviour tree.
        ActiveSelector *rootNode;

        //Type of behaviour.
        Enumeration::IABehaviour behaviour;

        //Behaviour of the AI.
        std::string chosenBehaviour;

        //All choices the AI can do.
        std::vector<std::string> *choices;

        //Current choice of the AI.
        i32 choiceIndex;

        //Determine if the choice of the Ai is updated fast or not. True will be the fast mode and false the slow.
        bool fast;

        //Timer used to update fast the AI's choices.
        Timer* updateFastTimer;

        //Timer used to update slow tha AI's choices.
        Timer* updateSlowTimer;
};

#endif