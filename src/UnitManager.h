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
         * 
         * @param The Enumeration::Team is the team to which belongs the unit manager: Enumeration::Team::Human or Enumeration::Team::IA. 
         * @param The std::string is the civilization to which belongs the unit manager: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
         */
        UnitManager(Enumeration::Team, std::string);

        /**
         * @brief Unit destructor.
         */
        virtual ~UnitManager();

        /**
         * @brief Create a troop if the player can pay it.
         * 
         * @param The std::string is the type of unit that is going to be created.
         * @return True if the troop is created and false in other case.
         * @see checkCanPay(std::string) method.
         */
        bool createTroop(std::string);

        /**
         * @brief Check if there is not a current troop being deployed and start deploying the troop selected.
         * 
         * @param The i32 is the id of the troop that is going to be deployed.
         */
        void startDeployingTroop(i32);

        /**
         * @brief Deploy the selected troop from the command center to the map.
         * 
         * @param The Vector3 is the position where the troop is going to move to from the command center.
         */
        void deploySelectedTroop(Vector2<f32>);

        /**
         * @brief Check if there is not a current troop being deployed and start deploying all the troops that are in the command center.
         */
        void startDeployingAllTroops();

        /**
         * @brief Deploy all the troops from the command center to the map.
         * 
         * @param The Vector3 is the position where the troops are going to move to from the command center.
         */
        void deployAllTroops(Vector2<f32>);

        /**
         * @brief Retract all the player's troops from the map to the command center.
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
         * 
         * @param The i32 is the id of the troop in inMapTroops that is going to be selected.
         */
        void selectTroop(i32);

        /**
         * @brief
         * 
         * @param
         */
        void startBattle(i32);

        /**
         * @brief Delete the unit with the id passed by parameter.
         * 
         * @param The i32 is the id of the unit that is going to be deleted. 
         */
        void deleteUnit(i32);

        /**
         * @brief Check if there is any troop salected.
         * 
         * @return True when there is a troop selected and false in other case.
         */
        bool isTroopSelected();

        /**
		 * @brief Check if the player's metalAmount and crystalAmount variables are higher than the ones passed by parameter.
		 * 
         * @param metalCost is the metal cost of the unit.
		 * @param crystalCost is the crystal cost of the unit.
         * @param citizensCost is the citizens cost of the unit.
		 * @return True if the three player's variables are higher than the three passed by parameter and false in other case.
		 */
		bool isSolvent(i32 metalCost, i32 crystalCost, i32 citizensCost);

        /** 
         * @brief Responsible for managing calls to isSolvent() for the human player, registering the type of the desired unit and sending the aforementhioned method the prices.
		 * 
         * @param The std::string is the unit type.
		 * @return True when isSolvent() returns true and false in other case.
		 */
        bool checkCanPay(std::string);

        /**
         * @brief Get the value of deployingTroop variable.
         * 
         * @return True when there is any troop being deployed and false in other case.
         */
        bool isDeployingTroop();

        /**
         * @brief Check if there are no troops in the player's command center.
         * 
         * @return True if there are no troops in the player's command center and false in other case.
         */
        bool areTroopsDeployed();

        /**
         * @brief Check if there is any player's troop in the map.
         * 
         * @return True if there is any player's troop in the map and fals in other case.
         */
        bool areTroopsInMap();

        /**
         * @brief Get the troop that is at the same position as the mouse cursor.
         * 
         * @return i32 that will be the id of the troop at the position of the mouse cursor or -1 if there is no troop at that point. 
         */
		i32 getCollisionID();

        /**
         * @brief Get the player's amount of troops of the type passed by parameter.
         * 
         * @param The std::string is the type of unit.
         * @return i32 that will be the player's amount of troops of the type of unit.
         */
        i32 getTroopAmount(std::string);

        /**
         * @brief Get the player's amount of troops.
         * 
         * @return i32 that will be the player's amount of troops.
         */
        i32 getTotalTroopAmount();

        /**
         * @brief Get the id of the troop that is being deployed.
         * 
         * @return i32 that will be the value of currentDeployingTroop variable or -1 if there is no tropp being deployed.
         */
        i32 getDeployingTroopID();

        /**
         * @brief Get the current selected troop.
         * 
         * @return A pointer to an Unit object that will be the value of selectedTroop variable.
         */
        Unit* getSelectedTroop();

        /**
         * @brief Get the troops that are in the queue to be trained.
         * 
         * @return A pointer to a std::map object that will be the value of inQueueTroops variable.
         */
        std::map<i32, Unit*> *getInQueueTroops();

        /**
         * @brief Get the troops that are in the player's command center.
         * 
         * @return A pointer to a std::map object that will be the value of inHallTroops variable.
         */
        std::map<i32, Unit*> *getInHallTroops();

        /**
         * @brief Get the troops that are in the map.
         * 
         * @return A pointer to a std::map object that will be the value of inMapTroops variable.
         */
        std::map<i32, Unit*> *getInMapTroops();

        /**
         * @brief
         * 
         * @return
         */
		std::string getCollisionName();
        
        /**
         * @brief
         * 
         * @return
         */
		const UnitData& getUnitData(std::string) const;

    private:
        //Player's team: Enumeration::Team::Human or Enumeration::Team::IA.
        Enumeration::Team team;

        //Layer were the units are going to be created.
        SceneNode *unitLayer;

        //
		SceneNode *currentCollision;

        //
        std::map<std::string, UnitData> baseUnits;

        //Pointer to a std::map object with all the units that are being trained.
        std::map<i32, Unit*> *inQueueTroops;

        //Pointer to a std::map object with all the units that are in the command center.
        std::map<i32, Unit*> *inHallTroops;

        //Pointer to a std::map object with all the units that are in the map.
        std::map<i32, Unit*> *inMapTroops;

        //Amount of troops created of each type.
        std::map<std::string, i32> troopsAmount;

        //Pointer to an Unit object with the current unit selected. If there is none selected it will be nullptr.
        Unit *selectedTroop;

        //True if there is a troop being deployed and false in other case.
        bool deployingTroop;

        //Id of the current troop that is being deployed.
        i32 currentDeployingTroop;

        //Id number that is going to be asigned as the key of the next unit created.
        i32 nextTroopId;

        
};

#endif