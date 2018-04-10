#ifndef TROOP_H
#define TROOP_H
#include <vector>
#include "Types.h"
template<class T>
class Vector3;
template<class T>
class Vector2;
class Model;
class SceneNode;
class Troop{
    private:
        i32 max;
        i32 actualIndex;
        std::vector< Model* > modelVector;
        std::vector< Vector2<f32> > positionVector; 

        f32 alignmentWeight;
        f32 cohesionWeight;
        f32 separationWeight;
        /* Flocking */
        Vector2<f32> alignment();
        Vector2<f32> cohesion();
        Vector2<f32> separation();
        Vector2<f32> calculateFlocking();
    public:
        Troop(SceneNode *, const wchar_t *, i32 qnty, i32 ID);
        ~Troop();
        void setPosition(Vector2<f32> vectorPos);
        void moveTroops(Vector2<f32> vectorMov);
        void setActive(bool data);
};
#endif /* TROOP_H */