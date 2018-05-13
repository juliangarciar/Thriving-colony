#ifndef BOX2D_H
#define BOX2D_H
//-----------------------------------------------------------------------------
//
//  Name:   InvertedAABBox2D.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   v simple inverted (y increases down screen) axis aligned bounding
//          box class
//
//  Modified: Julian Garcia Ruiz 
//-----------------------------------------------------------------------------

#include "Vector2.h"
#include <Types.h>
class Box2D
{
    private:
    // Top-left point
        Vector2<f32>  m_vTopLeft;
    // Top-right point
        Vector2<f32>  m_vBottomRight;
    // Center point
        Vector2<f32>  m_vCenter;

        Vector2<f32> m_vTopRight;
        Vector2<f32> m_vBottomLeft;
        
        f32 halfSizeX;
        f32 halfSizeY;
    public:
        Box2D();
        Box2D(f32 sizeX, f32 sizeY);
    // Constructor
        Box2D(Vector2<f32> tl, Vector2<f32> br);
        //Box2D(Vector2<f32> _pos, f32 halfsize);
    /* Move hitbox */
        void moveHitbox(f32 x, f32 y);
        void moveHitbox(Vector2<f32> _vectorPos);
    // Getters
        Vector2<f32> TopLeft();
        Vector2<f32> BottomRight();
        Vector2<f32> TopRight();
        Vector2<f32> BottomLeft();
        Vector2<f32> Center();
        f32    Top();
        f32    Left();
        f32    Bottom();
        f32    Right();
        Box2D getAmplifiedBox(f32 distance);
        bool isOverlappedWith(Box2D other);
};
  
#endif /* BOX2D_H */