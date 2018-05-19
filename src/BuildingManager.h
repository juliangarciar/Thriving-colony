#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <map>
#include <Types.h>
#include <Enumeration.h>
#include <Building.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Model.h>

/**
 * @class BuildingManager.
 * @brief Create a BuildingManager type object.
 */
class BuildingManager {

	public:
		/**
		 * @brief BuildingManager constructor.
		 * 
		 * @param Enumeration::Team is the team to which belongs the building manager: Enumeration::Team::Human or Enumeration::Team::IA.
		 * @param std::string is the civilization to which belongs the building.
		 */
		BuildingManager(Enumeration::Team, std::string);

		/**
		 * @brief BuildingManager destructor.
		 */
		virtual ~BuildingManager();

		/**
		 * @brief Check if the mouse pointer is on any building while buildingMode variable is false. The value of the currentCollision variable is modified to a new SceneNode with the new position of the mouse data.
		 */
		void testRaycastCollisions();

		/**
		 * @brief Set the value of the buildingMode variable to true if the building can be paid and the value of the buildingMode variable is false. Change the value of tempBuilding value to a new Building.
		 * 
		 * @param std::string is the type of building of the new Building at temBuilding.
		 * @return True if the value of the buildingMode variable is modified and false if it is not.
		 */
		bool setBuildingMode(std::string);

		/**
		 * @brief Create a new building at the point where the mouse is if it is not occupied and the left botton of the mouse is pressed. If the right botton of the mouse is pressed, delete the tempBuilding variable and set it to MULL. Set buildingMode to false.
		 */
		void drawBuilding();

		/**
		 * @brief create and build building
		 * 
		 * @param Vector3<f32> is the position where the building is going to be created.
		 * @param std::string is the building type.
		 * @param i32 is the buildingTime (if < 0 it takes the original).
		 */
		void createBuilding(Vector2<f32>, std::string, i32 = -1);

		/**
		 * @brief Set all the variables needed for the building at tempBuilding variable to be displayed and insert it at the buildings variable as its key as the value of the nextBuildingId. Set the tempBuilding variable to nullptr and add 1 to the nextBuildingId variable.
		 * 
		 * @param Vector3<f32> is the position where the building is going to be created.
		 */
		void buildBuilding(Vector2<f32>);

		/**
		 * @brief Responsible for managing calls to isSolvent() for the human player, registering the type of the desired building and sending the aforementhioned method the prices. It has its own method to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
		 * 
		 * @param std::string is the building type.
		 * @return True when isSolvent() returns true and false in other case.
		 */
		bool checkCanPay(std::string);
		
		/**
		 * @brief Check if the building with the key passed by parameter is finished or not.
		 * 
		 * @param i32 is the key of the building that is going to be checked.
		 * @return True when it is finished and false in other case.
		 */
		bool checkFinished(i32);

		/**
		 * @brief Get the ID number of the mesh of currentCollision variable.
		 * 
		 * @return i32 with the ID of the mesh if the currentCollision variable if it is not nullptr and -1 in other case.
		 */
		i32 getCollisionID();
		
		/**
		 * @brief Get the building stored in buildings variable associated to key passed by parameter.
		 * 
		 * @param i32 is the key associated to the building that is going to be returned.
		 * @return A pointer to an object of Building type if the i32 passed by parameter matches with the key of one building stored in the buildings variable or nullptr in other case.
		 */
		Building *getBuilding(i32);

		/**
		 * @brief Get all player's buildings built.
		 * 
		 * @return Value of the buildings variable.
		 */
		std::map<i32, Building*>* getBuildings();

		/**
		 * @brief Get the layer where the buildings are built.
		 * 
		 * @return Value of the buildingLayer variable.
		 */
		SceneNode* getBuildingLayer();

		/**
		 * @brief Delete the building stored in the buildings variable wich key is the one passed by parameter. Modifies happiness variable of class Player.
		 * 
		 * @param i32 is the key associated to the building that is going to be deleted.
		 * @see decreaseHappiness(i32) of class Player.
		 */
		void deleteBuilding(i32);

		/**
		 * @brief Get the amount of one type of building that the player has built.
		 * 
		 * @param std::string is the type of building that is going to be checked.
		 * @return i32 that is the amount of buildings of this type.
		 */
		i32 getAmount(std::string);

		/**
		 * @brief Get the Building Data object
		 * 
		 * @return BuildingData 
		 */
		const BuildingData& getBuildingData(std::string) const;

	private:
		//Player's team: Enumeration::Team::Human or Enumeration::Team::IA.
		Enumeration::Team team;

		//Id number that is going to be asigned as the key of the next building built.
		i32 nextBuildingId;

		//True if there is a building selected to be built and false in other case.
        bool buildingMode;
		
		//Layer were the buildings will be built.
		SceneNode *buildingLayer;

		//Current colliding layer.
		i32 currentCollisionID;
		
		//Temporary building that is used when a building is selected to be built.
		Building *tempBuilding;

		//List of buildings.
		std::map<std::string, BuildingData> baseBuildings;

		//Amount of buildings built of each type.
		std::map<std::string, i32> buildingAmounts;

		//All buildings built stored with their id as key.
		std::map<i32, Building*> *inMapBuildings;
};

#endif