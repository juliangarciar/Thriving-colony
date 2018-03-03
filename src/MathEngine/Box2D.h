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
    public:
        Box2D();
    // Constructor
        Box2D(Vector2<f32> tl, Vector2<f32> br);

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
};
  
#endif /* BOX2D_H */