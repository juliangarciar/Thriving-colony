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
		void setBuildingMode(Enumeration::BuildingType);
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
		void buildBuilding(Vector3<float>, Enumeration::BuildingType, bool = false);

		/**
		 * @brief Comprueba si el jugador tiene recursos necesarios para comprar el edificio
		 * @param metal es el coste de metal del edificio
		 * @param cristal es el coste de cristal del edificio
		 * @param team es el equipo al que pertenecera el edificio
		 * @return true si es solvente y false, en caso contrario
		 */
		bool isSolvent(int, int);
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
		bool checkFinished(int);

		/**
		 * @brief Actualiza el manejador de edificios
		 */
		void updateBuildingManager();
		/**
		 * @brief Asigna, al edificio que se esta construyendo, el modelo 3D asociado
		 * @param coordenadas donde colocar el modelo 3D
		 * @param buildingType es el tipo de edificio que se construye
		 * @param team es el equipo al que pertece el edificio
		 */
		void setTempBuildingModel(Vector3<float>, Enumeration::BuildingType);
		
		/**
		 * @brief Solicita el id de la colision
		 * @return id de tipo entero
		 */
		int getCollisionID();
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
		Building *getBuilding(int);
		/**
		 * @brief Solicita los edificios del mapa
		 * @return devuelve un objeto de tipo hash map con los edificios y sus IDs asociadas
		 */
		std::map<int, Building*>* getBuildings();
		/**
		 * @brief Solicita la capa en la que esta edificio
		 * @return layer de tipo SceneNode
		 */
		SceneNode* getBuildingLayer();
		/**
		 * @brief Obtiene la cantidad de edificios de cualquier tipo
		 * @param tipo de edificio
		 * @return cantidad
		 */
		int getAmount(Enumeration::BuildingType);
	private:
		Enumeration::Team team;
		Enumeration::BreedType breed;

		int nextBuildingId;
        int gridAlignment;
        bool buildingMode;
		
		SceneNode *buildingLayer;
		SceneNode *currentCollision;

		std::map<int, Building*> *buildings;
		
		Building *tempBuilding;

		int buildingAmounts[Enumeration::BuildingType::BuildingsSize];
};

#endif