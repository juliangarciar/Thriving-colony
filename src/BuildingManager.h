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

class BuildingManager {
	public:
		BuildingManager();
		virtual ~BuildingManager();

		void testRaycastCollisions();
		int getCollisionID();
		std::string getCollisionName();

		std::map<int, Building*>* getBuildings();

		void setBuildingMode(Enumeration::BuildingType);
        void drawBuilding(Terrain *terrain);
		void buildBuilding(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);

		bool isSolvent(int, int, Enumeration::Team);
		bool checkCanPay(Enumeration::BuildingType);

		void updateBuildingManager();
		bool checkFinished(int);

		void setTempBuildingModel(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);
		void buildInitialBuilding();
		
		SceneNode* getBuildingLayer();
	private:
		int id;
        int gridAlignment;
        bool buildingMode;
		
		SceneNode *buildingLayer;
		SceneNode *currentCollision;
		std::map<int, Building*> *buildings;

		Building *tempBuilding;
};

#endif