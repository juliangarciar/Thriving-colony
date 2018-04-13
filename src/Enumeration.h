#ifndef ENUMERATION_H
#define ENUMERATION_H

/**
 * @class Enumeration.
 * @brief Set the enumerations that are going to be needed.
 */
class Enumeration {
    public:

        //Civilizations.
        enum BreedType {
            Drorania,
            Kaonov
        };

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

        //Building types.
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
            Workshop,
            BuildingsSize
        };

        //Unit types.
        enum UnitType {
            StandardR,
            AdvancedR,
            StandardM,
            AdvancedM,
            Launcher,
            Desintegrator,
            Idol,
            TroopsSize
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

        //Metal and crystal costs of each building.
        enum BuildingCost {
            SchoolMetalCost = 500,
            SchoolCrystalCost = 0,

            MarketMetalCost = 800,
            MarketCrystalCost = 0,

            HospitalMetalCost = 800,
            HospitalCrystalCost = 0,

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

        //Cells occupied by each building.
        enum BuildingCells{
            MainCells = 3,
            SchoolCells = 2,
            MarketCells = 2,
            HospitalCells = 3,
            SiderurgyCells = 3,
            QuarryCells = 3,
            HomeCells = 1,
            BarrackCells = 3,
            BarnCells = 2,
            WorkshopCells = 2,
            WallCells = 1,
            TowerCells = 1

        };

        //
        enum BuildingHalfsize{
            MainHalfsize = 120,
            SchoolHalfsize = 80,
            MarketHalfsize = 80,
            HospitalHalfsize = 120,
            SiderurgyHalfsize = 120,
            QuarryHalfsize = 120,
            HomeHalfsize = 40,
            BarrackHalfsize = 80,
            BarnHalfsize = 80,
            WorkshopHalfsize = 80,
            WallHalfsize = 40,
            TowerHalfsize = 40
        };

        //Metal and crystal costs of each unit.
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

        //IO states.
        enum ioStatesENUM {
            PRESSED, 
            RELEASED, 
            UP, 
            DOWN
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

        //AI types of behaviour.
        enum IABehaviour {
            VeryHappy,
            Happy,
            Neutral,
            Unhappy,
            VeryUnhappy
        };

        //Entity types.
        enum EntityType {
            Building,
            Unit
        };

        //Amount of happiness provided by each building.
        enum HappinessProvided {
            AmountHappinessBarn = 0,
            AmountHappinessBarrack = 0,
            AmountHapppinesHospital = 40,
            AmountHappinessHouse = 1,
            AmountHappinessMarket = 30,
            AmountHappinessQuarry = 0,
            AmountHappinessSchool = 20,
            AmountHappinessSiderurgy = 0,
            AmountHappinessTower = 1,
            AmountHappinessWall = 1,
            AmountHappinessWorkshop = 0
        };
        
        //Position of the AI's command center.
        enum IACityHall {
            ia_x = 2000,
            ia_z = 2000
        };

        //Position of the Human's command center.
        enum HumanCityHall {
            human_x = 8000,
            human_z = 8000
        };

        //Margins of the map.
        enum MapMargins {
            mapMarginTop = 1500,
            mapMarginLeft = 1500,
            mapMarginBottom = 8500,
            mapMarginRight = 8500
        };

        //Army level provided by each type of unit.
        enum ArmyLevel {
            Footmen = 5,
            Mounted = 10,
            Siege = 7,
            Creatures = 15
        };

    private:
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
};

#endif