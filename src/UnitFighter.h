#ifndef UNITFIGHTER_H
#define UNITFIGHTER_H

#include "Types.h"
#include "MathEngine/Vector2.h"
#include "GraphicEngine/Animation.h"
#include "Enumeration.h"
#include <vector>

//class Model;
class Timer;
class Unit;
class UnitFighter{
    public:
        UnitFighter(SceneNode* _parent, Unit* _unitLeader, std::string _path, f32 _speed, f32 _attackRange, i32 _fighterIndex);
        ~UnitFighter();

        // Setters
        void setPosition(Vector2<f32> _pos);
        void setDestiny(Vector2<f32> _dest);
        void move();
        void update();
        void setNearFighters(std::vector<UnitFighter*>& _nearFighters);
        void setActive(bool _active);
		void switchState(Enumeration::UnitFighterState _state);

        // Getters
        Vector2<f32> getVectorPosition() const;
        Vector2<f32> getVectorSpeed() const;
        Vector2<f32> getVectorDestiny() const;
        const f32 getSpeed() const;
    private:
        /* Private functions */
        void ufAttackState();
        void ufMoveState();
        void ufIdleState();
        void ufConfrontState();
        bool inRange();
        bool hasArrived();
        Vector2<f32> calculateFlocking();
        void calculateDirection();
        void rotateFighter();
        /* Privamente member variables */
        Unit* unitLeader;
        Animation* fighterModel;
        const f32 speed;
        const f32 attackRange;
        const i32 fighterIndex;
        //bool isMoving;
        Vector2<f32> vectorPosition;
        Vector2<f32> vectorSpeed;
        Vector2<f32> vectorDestiny;
        Vector2<f32> vectorDirection;
        const f32 maxDesviation;
        f32 maxTime;
        f32 rotationAngle;
        Timer* unitFighterClock;
        Timer* rotationClock;
        /* Check in the future */
        std::vector<UnitFighter*> nearFighters;
        Enumeration::UnitFighterState fighterState;
};
#endif /* UNITFIGHTER_H */