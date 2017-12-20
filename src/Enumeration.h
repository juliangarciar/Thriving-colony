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
            GUI_ID_CREATE_MACHINE_BUTTON
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