#include "VeryHappyTree.h"

VeryHappyTree::VeryHappyTree(IA *iaPnt) {
    BehaviourTree BehaviourTree(iaPnt);

    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCriatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;

    metalThreshold = 1.5;
    crystalThreshold = 1.2;
    citizensThreshold = 2.5;
    armyThreshold = 0.1;
    meleeThreshold = 0.6;
}

VeryHappyTree::~VeryHappyTree() {

}

void BehaviourTree::makeChoice() { //Es asi?
    //First branch: Services
    if (ia->getHappiness() < happinessThreshold) {
        //To do: Elegir el servicio a construir
    } else {
        //Second branch: Resources
        //First subbranch: Siderurgy
        if (calculateMetalProductionRate() < metalThreshold) {
            //To do: Construir siderurgia
        } else {
            //Second subbranch: Quarry
            if (calculateCrystalProductionRate() < crystalThreshold && ia->getCityLevel() >= quarryMilestone) {
                //To do: Construir cantera
            } else {
                //Third branch: Homes
                if (calculateCitizensRate() < citizensThreshold) {
                    //ToDo: Construir viviendas
                } else {
                    //Fourth branch: Army
                    //First subbranch: Units
                    if (calculateArmyCitizensRate() < armyThreshold) {
                        //First subsubbranch: Melee
                        if (calculateMeleeRate() < meleeThreshold) {
                            //First subsubsubbranch: With criature
                            if (ia->getCityLevel() >= mountedCriatureMilestone) {
                                //To do: generar melees en criatura
                            } else {
                                //Second subsubsubbranch: Without criature
                                //To do: generar melees
                            }
                        } else {
                            //First subsubsubbranch: With criature
                            if (ia->getCityLevel() >= mountedCriatureMilestone) {
                                //To do: generar rango en criatura
                            } else {
                                //Second subsubsubbranch: Without criature
                                //To do: generar rango
                            }
                        }
                    } else {
                        //Second subbranch: Buildings
                        //First subsubranch: Wall
                        if (ia->getCityLevel() >= wallMilestone && ia->getWallBuilt() != true) {
                            //To do: construir muralla
                        } else {
                            //Second subsubbranch: Tower
                            if (ia->getCityLevel() >= towerMilestone) {
                                //To do: construir torre
                            } else {
                                //Third subsubbranch: Barrack
                                if (ia->getBarrackBuilt() != true){
                                    //To do: construir barraca
                                } else {
                                    //Fourth subsubbranch: Barn
                                    if (ia->getCityLevel() >= barnMilestone && ia->getBarnBuilt() != true) {
                                        //To do: construir establo
                                    } else {
                                        //Fifth subsubbranch: Workshop
                                        if (ia->getCityLevel() >= workshopMilestone && ia->getWorkshopBuilt() != true) {
                                            //To do: construir taller
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