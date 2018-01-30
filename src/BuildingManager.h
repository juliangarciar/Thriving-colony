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
		 */
		BuildingManager();
		/**
		 * @brief Destructor
		 */
		virtual ~BuildingManager();

		/**
		 * @brief Comprueba las colisiones con el Raycast
		 */
		void testRaycastCollisions();
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
		 * @brief Solicita los edificios del mapa
		 * @return devuelve un objeto de tipo hash map con los edificios y sus IDs asociadas
		 */
		std::map<int, Building*>* getBuildings();

		/**
		 * @brief asigna que un edificio este en construccion
		 * @param entero con el tipo de edificio que se esta construyendo
		 */
		void setBuildingMode(Enumeration::BuildingType);
		/**
		 * @brief dibuja el edificio a construir en el terreno
		 * @param terrain donde se indica el terreno en el que construir
		 */
		void drawBuilding(Terrain *terrain);
		/**
		 * @brief Construye el edificio
		 * @param coordenadas en las que se tiene que construir
		 * @param buildingType con el tipo de edificio a construir
		 * @param team indicando el equipo al que pertenece el edificio
		 */
		void buildBuilding(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);

		/**
		 * @brief Solicita los edificios del mapa
		 * @return 
		 */
		bool isSolvent(int, int, Enumeration::Team);
		/**
		 * @brief Solicita los edificios del mapa
		 */
		bool checkCanPay(Enumeration::BuildingType);

		/**
		 * @brief Solicita los edificios del mapa
		 */
		void updateBuildingManager();
		/**
		 * @brief Solicita los edificios del mapa
		 */
		bool checkFinished(int);

		/**
		 * @brief Solicita los edificios del mapa
		 */
		void setTempBuildingModel(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);
		/**
		 * @brief Solicita los edificios del mapa
		 */
		void buildInitialBuilding();
		
		/**
		 * @brief Solicita los edificios del mapa
		 */
		SceneNode* getBuildingLayer();
	private:
		SceneNode *buildingLayer;
		SceneNode *currentCollision;
		//std::vector< Box3D<float> > *buildings;
		//std::vector<Building*> *buildings;
		std::map<int, Building*> *buildings;
        bool buildingMode;
        int gridAlignment;

		//ToDo: no se yo esto...
		Building *tempBuilding;
		int id;
};

#endif