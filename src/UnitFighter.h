#ifndef UNITFIGHTER_H
#define UNITFIGHTER_H

#include "Types.h"
#include "MathEngine/Vector2.h"
#include "GraphicEngine/Model.h"
#include <vector>

//class Model;
class Timer;
class UnitFighter{
    public:
        UnitFighter(SceneNode* _parent, i32 _id, std::string _path, f32 _speed);
        ~UnitFighter();

        // Setters
        void setPosition(Vector2<f32> _pos);
        void setDestiny(Vector2<f32> _dest);
        void move();
        void update();
        void setNearFighters(std::vector<UnitFighter*>& _nearFighters);
        void setActive(bool _active);
        // Getters
        Vector2<f32> getVectorPosition() const;
        Vector2<f32> getVectorSpeed() const;
        Vector2<f32> getVectorDestiny() const;
        const f32 getSpeed() const;
    private:
        Model* fighterModel;
        const f32 speed;
        bool isMoving;
        Vector2<f32> vectorPosition;
        Vector2<f32> vectorSpeed;
        Vector2<f32> vectorDestiny;
        Vector2<f32> vectorDirection;
        const f32 maxDesviation;
        f32 maxTime;
        Timer* unitFighterClock;
        /* Check in the future */
        std::vector<UnitFighter*> nearFighters;
        
        bool hasArrived();
        Vector2<f32> calculateFlocking();
        void calculateDirection();
};
#endif /* UNITFIGHTER_H */