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

        enum UnitType {
            MeleeFootman,
            MeleeMounted,
            Creature,
            RangedFootman,
            RangedMounted,
            Catapult,
            Ram
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
            Attacking,
            BeingAttacked,
            DeployTroops,
            RetractTroops,
            StopBeingAttack
        }; 

        enum idGUI {
            ID0,
            GUI_ID_BUILDING_BUTTON,
            GUI_ID_QUIT_BUTTON
        };
        

    private:
        
};

#endif