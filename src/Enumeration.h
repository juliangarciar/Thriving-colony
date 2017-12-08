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

        enum EventType {
            Attacking,
            BeingAttacked,
            DeployTroops,
            RetractTroops,
            StopBeingAttack
        };

    private:
        
};

#endif