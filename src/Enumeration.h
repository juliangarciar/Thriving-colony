#ifndef ENUMERATION_H
#define ENUMERATION_H

class Enumeration {
    public:
        enum BuildingType {
            MainBuilding,
            Barn,
            Barrack,
            Hospital,
            House,
            Market,
            Quarry,
            Siderurgy,
            School,
            Tower,
            Wall,
            Workshop
        };

        enum BreedType {
            Drorania,
            Kaonov
        };

        enum Team {
            Human,
            IA
        };

        enum EventType {
            //IA
            CloseDoorsIA,
            DeployTroopsIA,
            OpenDoorsIA,
            RetractTroopsIA,

            //Human
            CloseDoorsHuman,
            DeployTroopsHuman,
            OpenDoorsHuman,
            RetractTroopsHuman,

            //Text
            DisableText,
            EnableText
        }; 

        //Old buttons
        enum idGUI {
            ID0,

            GUI_ID_BUILD_BARN_BUTTON,
            GUI_ID_BUILD_BARRACK_BUTTON,
            GUI_ID_BUILD_HOSPITAL_BUTTON,
            GUI_ID_BUILD_HOME_BUTTON,
            GUI_ID_BUILD_MARKET_BUTTON,
            GUI_ID_BUILD_QUARRY_BUTTON,
            GUI_ID_BUILD_SIDERURGY_BUTTON,
            GUI_ID_BUILD_SCHOOL_BUTTON,
            GUI_ID_BUILD_TOWER_BUTTON,
            GUI_ID_BUILD_WALL_BUTTON,
            GUI_ID_BUILD_WORKSHOP_BUTTON,

            GUI_ID_QUIT_BUTTON,
            GUI_ID_CLOSE_PANEL_BUTTON,
            GUI_ID_PLAY_BUTTON,
            GUI_ID_RESUME_BUTTON,
            GUI_ID_MENU_BUTTON,
            
            GUI_ID_CREATE_MELEE_TROOP_BUTTON,
            GUI_ID_CREATE_RANGED_TROOP_BUTTON,
            GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON,
            GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON,
            GUI_ID_CREATE_MONSTER_BUTTON,
            GUI_ID_CREATE_MACHINE_BUTTON,

            GUI_ID_DEPLOY_TROOPS_BUTTON,
            GUI_ID_DEPLOY_ALL_TROOPS_BUTTON,

            GUI_ID_RETRACT_ALL_TROOPS_BUTTON,

            GUI_ID_EXPAND_TERRAIN_BUTTON,
            GUI_ID_OPEN_PANEL_BUTTON
        };

        enum BuildingCost {
            SchoolMetalCost = 500,
            SchoolCrystalCost = 0,

            MarketMetalCost = 800,
            MarketCrystalCost = 0,

            HospitalMetalCost = 800,
            HospitalCrystalCost = 300,

            SiderurgyMetalCost = 500,
            SiderurgyCrystalCost = 0,

            QuarryMetalCost = 2000,
            QuarryCrystalCost = 0,

            HomeMetalCost = 100,
            HomeCrystalCost = 0,

            BarrackMetalCost = 500,
            BarrackCrystalCost = 0,

            BarnMetalCost = 675,
            BarnCrystalCost = 230,

            WorkshopMetalCost = 725,
            WorkshopCrystalCost = 300,

            WallMetalCost = 75,
            WallCrystalCost = 0,

            TowerMetalCost = 300,
            TowerCrystalCost = 0,
        };

        enum UnitCost {
            MeleeFootmenMetalCost = 125,
            MeleeFootmenCrystalCost = 0,

            RangedFootmenMetalCost = 150,
            RangedFootmenCrystalCost = 0,

            MountedMeleeMetalCost = 235,
            MountedMeleeCrystalCost = 75,

            MountedRangedMetalCost = 245,
            MountedRangedCrystalCost = 75,

            CreatureMetalCost = 215,
            CreatureCrystalCost = 60,

            CatapultMetalCost = 265,
            CatapultCrystalCost = 160,

            RamMetalCost = 295,
            RamCrystalCost = 160,
        };

        //Unit types
        enum UnitType{
            StandardR,
            AdvancedR,
            Launcher,
            Desintegrator,
            StandardM,
            AdvancedM,
            Idol
        };

        //Game states
        enum State {
            MenuState,
            GameState,
            PauseState
        };

        // Enumeration for UP, DOWN, PRESSED and RELEASED key states. Also used for mouse button states.
        enum ioStatesENUM {
            PRESSED, 
            RELEASED, 
            UP, 
            DOWN
        };
        
        enum UnitState {
            Idle,
            Move,
            AttackMove,
            Attack,
            Chase
        };

        enum IAChoices {
            ClosingDoors,
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

        enum IABehaviour {
            VeryHappy,
            Happy,
            Neutral,
            Unhappy,
            VeryUnhappy
        };

        enum IACityHall {
            ia_x = 2000,
            ia_z = 2000
        };

        enum HumanCityHall {
            human_x = 8000,
            human_z = 8000
        };

        enum MapMargins {
            mapMarginTop = 1500,
            mapMarginLeft = 1500,
            mapMarginBottom = 8500,
            mapMarginRight = 8500
        };

    private:
        
};

#endif