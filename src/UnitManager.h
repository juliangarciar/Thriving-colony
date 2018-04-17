#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Unit.h"
#include <cstdlib>
#include <vector>
#include <map>
#include <Types.h>
#include <GraphicEngine/Terrain.h>
#include <SoundEngine/SoundSystem.h>
#include <PathPlanner/PathManager.h>
#include "Enumeration.h"

/**
 * @class UnitManager.
 * @brief Create a UnitManager type object.
 */
class UnitManager{

    public:
        /**
         * @brief UnitManager constructor.
         * @param Enumeration::Team is the team to which belongs the unit manager: Enumeration::Team::Human or Enumeration::Team::IA. 
         * @param std::string is the civilization to which belongs the unit manager: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
         */
        UnitManager(Enumeration::Team, std::string);

        /**
         * @brief Unit destructor.
         */
        virtual ~UnitManager();

        /**
         * @brief Create a troop if the player can pay it.
         * @param std::string is the type of unit that is going to be created.
         * @return True if the troop is created and false in other case.
         * @see checkCanPay(Enumeration::UnitType) method.
         */
        bool createTroop(std::string);

        /**
         * @brief Check if there is not a current troop being deployed and start deploying the troop selected.
         * @param The i32 is the id of the troop that is going to be deployed.
         */
        void startDeployingTroop(i32);

        /**
         * @brief Deploy the selected troop from the command center to the map.
         * @param The Vector3 is the position where the troop is going to move to from the command center.
         */
        void deploySelectedTroop(Vector2<f32>);

        /**
         * @brief Check if there is not a current troop being deployed and start deploying all the troops that are in the command center.
         */
        void startDeployingAllTroops();

        /**
         * @brief Deploy all the troops from the command center to the map.
         * @param The Vector2 is the position where the troops are going to move to from the command center.
         */
        void deployAllTroops(Vector2<f32>);

        /**
         * @brief 
         * 
         */
        void retractAllTroops();

        /**
         * @brief Set currentCollision variable to the unit that is on the position of the current position of the mouse cursor.
         */
        void testRaycastCollisions();

        /**
         * @brief Update the troops.
         */
        void updateUnitManager();

        /**
         * @brief Change the icon of the mouse cursor to the one used when there is no troop selected.
         */
        void unSelectTroop();

        /**
         * @brief Change the state of the selected troop to Enumeration::UnitState::AttackMove when the A key is pressed and to Enumeration::UnitState::Move in other case.
         */
        void moveOrder();

        /**
         * @brief Set selectedTroop variable to the troop in inMapTroops variable that has the key that is the same number passed by parameter.
         * @param The i32 is the id of the troop in inMapTroops that is going to be selected.
         */
        void selectTroop(i32);

        /**
         * @brief
         * @param
         */
        void startBattle(i32);

        /**
         * @brief Delete the unit with the id passed by parameter.
         * @param The i32 is the id of the unit that is going to be deleted. 
         */
        void deleteUnit(i32);

        /**
         * @brief Check if there is any troop salected.
         * @return True when there is a troop selected and false in other case.
         */
        bool isTroopSelected();

        /**
         * @brief Check if the player's metalAmount and crystalAmount variables are higher than the ones passed by parameter.
         * @param i32 is the metal cost of the unit.
         * @param i32 is the crystal cost of the unit.
         * @param i32 is the citizen cost of the unit.
         * @return True if both player's variables are higher than the both passed by parameter and false in other case.
         */
	bool isSolvent(i32, i32, i32);

        /**
         * @brief Responsible for managing calls to isSolvent() for the human player, registering the type
         * of the desired unit and sending the aforementhioned method the prices.
         * @param std::string is the unit type.
         * @return True when isSolvent() returns true and false in other case.
         */
        bool checkCanPay(std::string);

        /**
         * @brief Get the value of deployingTroop variable.
         * @return True when there is any troop being deployed and false in other case.
         */
        bool isDeployingTroop();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool areTroopsDeployed();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool areTroopsInMap();

        //GETTERS
	i32 getCollisionID();
        i32 getTroopAmount(std::string);
        i32 getTotalTroopAmount();
        i32 getDeployingTroopID();
        Unit* getSelectedTroop();
        std::map<i32, Unit*> *getInQueueTroops();
        std::map<i32, Unit*> *getInHallTroops();
        std::map<i32, Unit*> *getInMapTroops();
	std::string getCollisionName();
    private:
        Enumeration::Team team;

        SceneNode *unitLayer;
	SceneNode *currentCollision;

        std::map<std::string, UnitData> baseUnits;

        std::map<i32, Unit*> *inQueueTroops;
        std::map<i32, Unit*> *inHallTroops;
        std::map<i32, Unit*> *inMapTroops;

        std::map<std::string, i32> troopsAmount;

        Unit *selectedTroop;

        bool deployingTroop;
        i32 currentDeployingTroop;

        i32 nextTroopId;
};

#endif