#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <vector>
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

		int getHoverBuilding();
		std::vector<Building*>* getBuildings();

		void setBuildingMode();
        void drawBuilding(Terrain *terrain, Enumeration::BuildingType, Enumeration::Team);
		void buildBuilding(Vector3<float>*, Enumeration::BuildingType, Enumeration::Team);

	private:
		SceneNode *buildingLayer;
		//std::vector< Box3D<float> > *buildings;
		std::vector<Building*> *buildings;
        bool buildingMode;
        int gridAlignment;

		//ToDo: no se yo esto...
		Model *cube;
};

#endif