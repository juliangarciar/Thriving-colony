#ifndef BOX2D_H
#define BOX2D_H

#include "Vector2.h"
#include <Types.h>
class Box2D
{
    public:
    // ToDo: Fix this two constructors
        Box2D();
        Box2D(Vector2<f32> vectorPosition, f32 sizeX, f32 sizeY);
    // Constructor
        Box2D(Vector2<f32> tl, Vector2<f32> br);
    /* Move hitbox */
        void moveHitbox(f32 x, f32 y);
        void moveHitbox(Vector2<f32> _vectorPos);
    // Getters
        Vector2<f32> TopLeft() const;
        Vector2<f32> BottomRight() const;
        Vector2<f32> TopRight() const;
        Vector2<f32> BottomLeft() const;
        Vector2<f32> Center() const;
        f32    Top() const;
        f32    Left() const;
        f32    Bottom() const;
        f32    Right() const;
        Box2D getAmplifiedBox(f32 distance) const;
        bool isOverlappedWith(const Box2D& other) const;

        i32 getCellsX() const;
        i32 getCellsY() const;
    private:
        Vector2<f32> m_vTopLeft;
        Vector2<f32> m_vBottomRight;
        Vector2<f32> m_vCenter;
        Vector2<f32> m_vTopRight;
        Vector2<f32> m_vBottomLeft;
        /* Super sida */
        i32 cellsX;
        i32 cellsY;
};
  
#endif /* BOX2D_H */