#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <string>
#include "Types.h"

struct baseUnit{
    baseUnit(std::string _name,
            i32 _move,
            i32 _damage,
            i32 _range,
            i32 _speed,
            i32 _radious,
            i32 _hp,
            i32 _time,
            i32 _happy,
            i32 _citizens,
            i32 _army,
            i32 _metal,
            i32 _crystal,
            i32 _troops,
            std::string _attEvent,
            std::string _mvEvent,
            std::string _selEvent,
            std::string _mdlPath,
            std::string _txtPath):unitName(_name),
                                    moveSpeed(_move),
                                    attackDamage(_damage),
                                    attackRange(_range),
                                    attackSpeed(_speed),
                                    viewRadious(_radious),
                                    maxHP(_hp),
                                    recruitingTime(_time),
                                    happines(_happy),
                                    citizens(_citizens),
                                    armyLevel(_army),
                                    metalCost(_metal),
                                    crystalCost(_crystal),
                                    troops(_troops),
                                    attackEvent(_attEvent),
                                    moveEvent(_mvEvent),
                                    selectEvent(_selEvent),
                                    modelPath(_mdlPath),
                                    texturePath(_txtPath){};
    std::string unitName;

    i32 moveSpeed, attackDamage, attackRange, attackSpeed,
        viewRadious, maxHP, recruitingTime, happines, citizens,
        armyLevel, metalCost, crystalCost, troops;

    std::string attackEvent; 
    std::string moveEvent;
    std::string selectEvent; 
    std::string modelPath;
    std::string texturePath;               
};

/* Add BaseBuilding */

#endif