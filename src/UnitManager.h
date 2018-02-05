#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <GraphicEngine/Terrain.h>
#include "Unit.h"
class UnitManager{
    public:
        UnitManager(Enumeration::Team teamData, Enumeration::BreedType raceData);
        virtual ~UnitManager();

        void testRaycastCollisions();

        void updateUnitManager();

        //Call for creating new troops, see the .cpp for more info on how to insert the desired unit
        bool createTroop(Enumeration::UnitType unitData);

        void deployTroopAtPosition(int index, Vector3<float> vectorData);
        void startDeployingTroop(int index);
        void deployTroop(Terrain *terrain);
        void deployAllTroops(Vector3<float> vectorData);

        void retractAllTroops(Vector3<float>);

        bool isTroopSelected();
        void selectTroop(int troopID);
        void unSelectTroop();
        void moveOrder(Terrain *terrain); //ToDo: usar el singleton
        void startBattle(int enemyID);

        bool isSolvent(int, int, Enumeration::Team);
        bool checkCanPay(Enumeration::UnitType);


        std::map<int, Unit*> * getInMapTroops();
        std::vector<Unit*> * getInHallTroops();
        int getTotalTroops(); 
        Unit* getSelectedTroop();
		int getCollisionID();
		std::string getCollisionName();

        int getTroopAmount(Enumeration::UnitType);

    private:
        SceneNode *unitLayer;

		SceneNode *currentCollision;

        std::vector<Unit*> *inHallTroops;
        std::map<int, Unit*> *inMapTroops;

        std::vector<Unit*> *totalTroops;

        Unit *selectedTroop;

        Enumeration::Team teamManager;
        Enumeration::BreedType breedType;

        bool isDeployingTroop;
        int currentDeployingTroop;

        int gridAlignment;
        
        int troopsAmount[Enumeration::UnitType::TroopsSize];
};

#endif