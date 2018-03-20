#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <map>
#include <Types.h>
#include <Enumeration.h>
#include <Building.h>
#include <MathEngine/Box3D.h>
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
		 * @brief BuildingManager onstructor.
		 * @param The Enumeration::Team is the team to which belongs the building manager: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param The Enumeration::BreedType is the civilization to which belongs the building manager: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
		 */
		BuildingManager(Enumeration::Team, Enumeration::BreedType);

		/**
		 * @brief BuildingManager destructor.
		 */
		virtual ~BuildingManager();

		/**
		 * @brief Check if the mouse pointer is on any building while buildingMode variable is false. 
		 * The value of the currentCollision variable is modified to a new SceneNode with the new position of the mouse data.
		 */
		void testRaycastCollisions();

		/**
		 * @brief Update the hitbox of each building at buildings variable.
		 * @see Use getNodeCollision(Mouse*) at SceneNode class.
		 */
		void recalculateHitbox();

		/**
		 * @brief Set the value of the buildingMode variable to true if the building can be paid and the value of the buildingMode variable is false.
		 * Change the value of tempBuilding value to a new Building.
		 * @param The Enumeration::BuildingType is the type of building of the new Building at temBuilding.
		 * @return True if the value of the buildingMode variable is modified and false if it is not.
		 */
		bool setBuildingMode(Enumeration::BuildingType);

		/**
		 * @brief Create a new building at the point where the mouse is if it is not occupied and the left bottom of the mouse is pressed.
		 * If the right bottom of the mouse is pressed, delete the tempBuilding variable and set it to MULL.
		 * Set buildingMode to false.
		 * @param terrain donde se indica el terreno en el que construir.
		 */
		void drawBuilding();

		/**
		 * @brief Set all the variables needed for the building at tempBuilding variable to be displayed and insert it at the buildings variable as its key as the value of the nextBuildingId.
		 * Set the tempBuilding variable to NULL and add 1 to the nextBuildingId variable.
		 * @param The Vector3<f32> is the position where the building is going to be created.
		 * @param The Enumeration::BuildingType is the building type.
		 * @param The bool will be true if the building is going to have an instant build and false if not.
		 */
		void buildBuilding(Vector3<f32>, Enumeration::BuildingType, bool = false);

		/**
		 * @brief Check if the player's metalAmount and crystalAmount variables are higher than the ones passed by parameter.
		 * @param metalCost is the metal cost of the building
		 * @param crystalCost is the crystal cost of the building
		 * @return True if both player's variables are higher than the both passed by parameter and false in other case.
		 */
		bool isSolvent(i32 metalCost, i32 crystalCost);

		/**
		 * @brief Responsible for managing calls to isSolvent() for the human player, registering the type
 		 * of the desired building and sending the aforementhioned method the prices. It has its own method
 		 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
		 * @param The Enumeration::BuildingType is the building type.
		 * @return True when isSolvent() returns true and false in other case.
		 */
		bool checkCanPay(Enumeration::BuildingType);
		
		/**
		 * @brief Comprueba si un edificio ha termiando de construirse o no
		 * @return true en caso de que este terminado y false, en caso contrario
		 */
		bool checkFinished(i32);

		/**
		 * @brief Actualiza el manejador de edificios
		 */
		void updateBuildingManager();
		
		/**
		 * @brief Solicita el id de la colision
		 * @return id de tipo entero
		 */
		i32 getCollisionID();
		/**
		 * @brief Solicita el nombre de la colision
		 * @return string con el nombre
		 */
		std::string getCollisionName();
		/**
		 * @brief Obtiene un edificio por su id
		 * @param id del edificio
		 * @return edificio
		 */
		Building *getBuilding(i32);
		/**
		 * @brief Solicita los edificios del mapa
		 * @return devuelve un objeto de tipo hash map con los edificios y sus IDs asociadas
		 */
		std::map<i32, Building*>* getBuildings();
		/**
		 * @brief Solicita la capa en la que esta edificio
		 * @return layer de tipo SceneNode
		 */
		SceneNode* getBuildingLayer();

		void deleteBuilding(i32);

		/**
		 * @brief Obtiene la cantidad de edificios de cualquier tipo
		 * @param tipo de edificio
		 * @return cantidad
		 */
		i32 getAmount(Enumeration::BuildingType);

	private:
		Enumeration::Team team;
		Enumeration::BreedType breed;

		i32 nextBuildingId;
        i32 gridAlignment;
        bool buildingMode;
		
		SceneNode *buildingLayer;
		SceneNode *currentCollision;

		std::map<i32, Building*> *buildings;
		
		Building *tempBuilding;

		i32 buildingAmounts[Enumeration::BuildingType::BuildingsSize];
};

#endif