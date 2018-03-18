#ifndef TROOP_H
#define TROOP_H
#include <vector>
#include "Types.h"
template<class T>
class Vector2;
class Model;
class SceneNode;
class Troop{
    private:
        i32 max;
        std::vector< Model* > modelVector;
        std::vector< Vector2<f32> > positionVector; 
    public:
        Troop(SceneNode *, const wchar_t *, i32 qnty, i32 ID);
        ~Troop();
        void setPosition(Vector2<f32> vectorPos);
        void moveTroops(Vector2<f32> vectorMov);
};
#endif /* TROOP_H */