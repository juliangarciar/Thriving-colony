#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <string>
#include "Types.h"

struct UnitData {
    std::string type;
    std::string modelPath;
    std::string texturePath;

    i32 metalCost;
    i32 crystalCost;
    i32 maxHP;
    i32 viewRadius;
    i32 attackRange;
    i32 attackDamage;
    i32 attackSpeed;
    i32 happinessVariation;
    i32 citizensVariation;

    i32 recruitingTime;
    i32 armyLevel; 
    i32 moveSpeed;
    i32 troops;

    std::string attackEvent; 
    std::string moveEvent;
    std::string selectEvent;      
};

struct BuildingData {
    std::string type;
    std::string modelPath;
    std::string texturePath;

    i32 metalCost;
    i32 crystalCost;
    i32 maxHP;
    i32 viewRadius;
    i32 attackRange;
    i32 attackDamage;
    i32 attackSpeed;
    i32 happinessVariation;
    i32 citizensVariation;
    
    f32 buildingTime;
    i32 cityLevel;
    i32 cellsX;
    i32 cellsY;
};

#endif