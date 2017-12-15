#ifndef ENUMERATION_H
#define ENUMERATION_H

class Enumeration {
    
    public:
        enum BuildingType {
            Barn,
            Barrack,
            Hospital,
            House,
            MainBuilding,
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

        enum EventType {
            Attacking,
            BeingAttacked,
            DeployTroops,
            RetractTroops,
            StopBeingAttack
        }; 

        enum idGUI {
            ID0,
            GUI_ID_BUILDING_BUTTON,
            GUI_ID_QUIT_BUTTON,
            GUI_ID_CLOSE_PANEL_BUTTON,
            GUI_ID_CREATE_TROOP_1_BUTTON,
            GUI_ID_CREATE_TROOP_2_BUTTON
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