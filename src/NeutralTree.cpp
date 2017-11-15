#include "NeutralTree.h"

NeutralTree::NeutralTree(IA* iaPnt) : BehaviourTree(iaPnt) {
    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 1.5;
    crystalThreshold = 1.2;
    citizensThreshold = 2.5;
    armyThreshold = 0.1;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;
}

NeutralTree::~NeutralTree() {
    
}

void BehaviourTree::developCity() { //Es asi?
    //First branch: Resources
    //First subbranch: Siderurgy
    if (calculateMetalProductionRate() < metalThreshold) {
        //To do: Construir siderurgia
    } else {
        //Second subbranch: Quarry
        if (calculateCrystalProductionRate() < crystalThreshold && ia->getCityLevel() >= quarryMilestone) {
            //To do: Construir cantera
        } else {
            //Second branch: Homes
            if (calculateCitizensRate() < citizensThreshold) {
                //ToDo: Construir viviendas
            } else {
                //Third branch: Services
                if (ia->getHappiness() < happinessThreshold) {
                    serviceBranch();
                } else {
                    //Fourth branch: Army
                    //First subbranch: Units
                    if (calculateArmyCitizensRate() < armyThreshold) {
                        unitsBranch();
                    } else {
                        //Second subbranch: Buildings
                        //First subsubbranch: Barrack
                        if (ia->getBarrackBuilt() != true){
                            //To do: construir barraca
                        } else {
                            //Second subsubbranch: Barn
                            if (ia->getCityLevel() >= barnMilestone && ia->getBarnBuilt() != true) {
                                //To do: construir establo
                            } else {
                                //Third subsubbranch: Workshop
                                if (ia->getCityLevel() >= workshopMilestone && ia->getWorkshopBuilt() != true) {
                                    //To do: construir taller
                                } else {
                                    //Fourth subsubranch: Wall
                                    if (ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true) {
                                        //To do: construir muralla
                                    } else {
                                        //Fifth subsubbranch: Tower
                                        if (ia->getCityLevel() >= towerMilestone) {
                                            //To do: construir torre
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}