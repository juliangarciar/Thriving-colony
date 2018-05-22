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

        //Unit fighter states.
        enum UnitFighterState{
            ufAttack,
            ufMove,
            ufIdle,
            ufConfront
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

        enum BehaviourState {
            Invalid,
            Success,
            Failure,
            Running
        };
};

#endif