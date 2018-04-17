#ifndef ENUMERATION_H
#define ENUMERATION_H

/**
 * @class Enumeration.
 * @brief Set the enumerations that are going to be needed.
 */
class Enumeration {
    public:
        //Teams.
        enum Team {
            Human,
            IA
        };

        //Game states.
        enum State {
            DefeatState,
            GameState,
            MenuState,
            WinState
        };

        //Entity types.
        enum EntityType {
            Building,
            Unit
        };

        //Event types.
        enum EventType {
            //AI events.
            DeployTroopsIA,
            RetractTroopsIA,

            //Human events.
            DeployTroopsHuman,
            RetractTroopsHuman,

            //Text events.
            showBuiltText,
            showRecruitedText
        };
        
        //Unit states.
        enum UnitState {
            Recruiting,
            InHome,
            Idle,
            Move,
            AttackMove,
            Attack,
            Chase,
            Retract
        };

        //IO states.
        enum ioStatesENUM {
            PRESSED, 
            RELEASED, 
            UP, 
            DOWN
        };

        //AI types of behaviour.
        enum IABehaviour {
            VeryHappy,
            Happy,
            Neutral,
            Unhappy,
            VeryUnhappy
        };

        //AI choices.
        enum IAChoices {
            DeployingTroops,
            TrainMeleeFootman,
            BuildBarrack,
            Attacking,
            RetractingTroops,
            BuildSchool,
            BuildMarket,
            BuildHospital,
            BuildSiderurgy,
            BuildQuarry,
            BuildHome,
            TrainMountedMelee,
            TrainCreature,
            TrainRangedFootman,
            TrainMountedRanged,
            TrainCatapult,
            TrainRam,
            BuildBarn,
            BuildWorkshop,
            BuildTower,
            BuildWall

        };
        
        //Margins of the map.
        enum MapMargins { //ToDo: to JSON
            mapMarginTop = 1500,
            mapMarginLeft = 1500,
            mapMarginBottom = 8500,
            mapMarginRight = 8500
        };
};

#endif