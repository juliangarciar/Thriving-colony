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

        enum Race {
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
        }; 

        enum idGUI {
            //Old buttons
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
            
            GUI_ID_CREATE_MELEE_TROOP_BUTTON,
            GUI_ID_CREATE_RANGED_TROOP_BUTTON,
            GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON,
            GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON,
            GUI_ID_CREATE_MONSTER_BUTTON,
            GUI_ID_CREATE_MACHINE_BUTTON,

            GUI_ID_DEPLOY_TROOPS_BUTTON
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

        //Special type, used to pass info to the UnitManager
        //in order to control which unit is created
        struct UnitType{
            enum Class{
                Ranged,
                Melee
            };

            enum SubClass
            {
                StandardR,
                AdvancedR,
                Launcher,
                Desintegrator,
                StandardM,
                AdvancedM,
                Idol
            };

            Class unitClass;
            SubClass unitSubClass;
        };

    private:
        
};

#endif