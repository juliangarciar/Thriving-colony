#include "VeryHappyTree.h"

VeryHappyTree::VeryHappyTree(IA* iaPnt) : BehaviourTree(iaPnt) {
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
                            //First subsubsubbranch: Creature
                            if (ia->getCityLevel() >= creatureMilestone) {
                                //To do: generar criatura
                            } else {
                                //First subsubsubbranch: With creature
                                if (ia->getCityLevel() >= mountedCreatureMilestone) {
                                    //To do: generar melees en criatura
                                } else {
                                    //Second subsubsubbranch: Without creature
                                    //To do: generar melees
                                }
                            }
                        } else {
                            //Second subsubbranch: Range
                            if (calculateRangeRate() < rangeThreshold) {
                                //First subsubsubbranch: With creature
                                if (ia->getCityLevel() >= mountedCreatureMilestone) {
                                    //To do: generar rango en criatura
                                } else {
                                    //Second subsubsubbranch: Without creature
                                    //To do: generar rango
                                }
                            } else {
                                //Third subsubbranch: Siege
                                if (calculateSiegeRate() < siegeThreshold) {
                                    //First subsubsubbranch: Ram
                                    if (ia->getRamAmount() <= ia->getCatapultAmount()) {
                                        //To do: generar ariete
                                    } else {
                                        //Second subsubsubbranch: Catapult
                                        //To do: generar catapulta
                                    }
                                }
                            }
                        }
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