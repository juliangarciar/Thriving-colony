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

class Box2D
{
    private:
    // Top-left point
        Vector2<f32>  m_vTopLeft;
    // Top-right point
        Vector2<f32>  m_vBottomRight;
    // Center point
        Vector2<f32>  m_vCenter;
    public:
    // Constructor
        Box2D(Vector2<f32> tl,
                        Vector2<f32> br):m_vTopLeft(tl),
                                        m_vBottomRight(br),
                                        m_vCenter((tl+br)/2.0)
        {}
    // Returns true if overlaps with another Box2D
        bool isOverlappedWith( Box2D& other)
        {
            return !((other.Top() > this->Bottom()) ||
                (other.Bottom() < this->Top()) ||
                (other.Left() > this->Right()) ||
                (other.Right() < this->Left()));
        }

    // Getters
        Vector2<f32> TopLeft(){
            return m_vTopLeft;
        }
        Vector2<f32> BottomRight(){
            return m_vBottomRight;
        }
        double    Top(){
            return m_vTopLeft.y;
        }
        double    Left(){
            return m_vTopLeft.x;
        }
        double    Bottom(){
            return m_vBottomRight.y;
        }
        double    Right(){
            return m_vBottomRight.x;
        }
        Vector2<f32> Center(){
            return m_vCenter;
        }
};
  
#endif /* BOX2D_H */