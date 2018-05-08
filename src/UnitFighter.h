#ifndef UNITFIGHTER_H
#define UNITFIGHTER_H

#include "Types.h"
#include "MathEngine/Vector2.h"
#include "GraphicEngine/Model.h"
#include <vector>

//class Model;
class UnitFighter{
    public:
        UnitFighter(SceneNode* _parent, i32 _id, std::string _path, f32 _speed);
        ~UnitFighter();

        // Setters
        void setPosition(Vector2<f32> _pos);
        void setDestiny(Vector2<f32> _dest);
        //void setSpeed(Vector2<f32> _spd);
        void move();
        void update(std::vector<UnitFighter*> &_nearFighters);
        //void setNearFighters(std::vector<UnitFighter*> &_nearFighters);

        // Getters
        Vector2<f32> getVectorPosition() const;
        Vector2<f32> getVectorSpeed() const;
        Vector2<f32> getVectorDestiny() const;
        const f32 getSpeed() const;
        //f32 getSpeed() const;
    private:
        Model* fighterModel;
        const f32 speed;
        bool isMoving;
        Vector2<f32> vectorPosition;
        Vector2<f32> vectorSpeed;
        Vector2<f32> vectorDestiny;
        Vector2<f32> vectorDirection;

        /* Check in the future */
        std::vector<UnitFighter*> nearFighters;
        
        void hasArrived() const;
        Vector2<f32> alignment();
        Vector2<f32> cohesion();
        Vector2<f32> separation();
        Vector2<f32> calculateFlocking();
        Vector2<f32> calculateDirection();
};
#endif /* UNITFIGHTER_H */