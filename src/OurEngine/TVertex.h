#ifndef TVERTEX_H
#define TVERTEX_H

#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Vector2.h>

class TVertex {
    public:
        TVertex(Vector3<f32>, Vector3<f32>, Vector2<f32>);
        ~TVertex();

        Vector3<f32> getPosition();
        Vector3<f32> getNormal();
        Vector2<f32> getTextureCoordinate();
    private:
        Vector3<f32> position;
        Vector3<f32> normal;
        Vector2<f32> textureCoordinate;
};

#endif