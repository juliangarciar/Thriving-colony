#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <map>
#include <irrlicht.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Model.h>
#include <Enumeration.h>
#include <Building.h>
#include <Types.h>

using namespace irr;

/**
 * @class BuildingManager
 * @brief Crea un objeto tipo BuildingManager
 */
class BuildingManager {
	public:
		/**
		 * @brief Constructor
		 * @param team
		 * @param breed
		 */
		BuildingManager(Enumeration::Team, Enumeration::BreedType);
		/**
		 * @brief Destructor
		 */
		virtual ~BuildingManager();

		/**
		 * @brief Comprueba las colisiones con el Raycast
		 */
		void testRaycastCollisions();
		/**
		 * @brief Actualiza las hitboxs
		 */
		void recalculateHitbox();

		/**
		 * @brief asigna que un edificio este en construccion
		 * @param entero con el tipo de edificio que se esta construyendo
		 */
		bool setBuildingMode(Enumeration::BuildingType);
		/**
		 * @brief dibuja el edificio a construir en el terreno
		 * @param terrain donde se indica el terreno en el que construir
		 */
		void drawBuilding();
		/**
		 * @brief Construye el edificio
		 * @param coordenadas en las que se tiene que construir
		 * @param buildingType con el tipo de edificio a construir
		 * @param instabuild
		 */
		void buildBuilding(Vector3<f32>, Enumeration::BuildingType, bool = false);

		/**
		 * @brief Comprueba si el jugador tiene recursos necesarios para comprar el edificio
		 * @param metal es el coste de metal del edificio
		 * @param cristal es el coste de cristal del edificio
		 * @param team es el equipo al que pertenecera el edificio
		 * @return true si es solvente y false, en caso contrario
		 */
		bool isSolvent(i32, i32);
		/**
		 * @brief Registra el tipo de edifio que se quiere construir y 
		 * maneja las llamadas al metodo isSolvent(), enviandole su precio.
		 * @param buildingType especificando el tipo de edicio a construir
		 * @return true si isSolvent()==true y false si !isSolvent()
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