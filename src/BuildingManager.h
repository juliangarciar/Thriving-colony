#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <vector>
#include <irrlicht.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Model.h>

using namespace irr;

class BuildingManager {
	public:
		BuildingManager();
		virtual ~BuildingManager();

		void getHoverBuilding();

		void setBuildingMode(bool mode);
        void drawCube(Terrain *terrain);
	private:
		SceneNode *buildingLayer;
		std::vector< Box3D<float> > buildings;
        bool buildingMode;
        int gridAlignment;

		//ToDo: no se yo esto...
		Model *cube;
};

#endif