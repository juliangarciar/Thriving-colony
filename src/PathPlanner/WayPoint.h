#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <Types.h>
#include <MathEngine/Vector2.h>


class WayPoint{
    private:
        i32 m_index;
        i32 cellIndex;
        Vector2<f32> m_vPosition;
    public:
        LWayPoint(Vector2<f32> position);
        ~LWayPoint();
    // Get / setters
        Vector2<f32> getPosition();
        void setPosition(Vector2<f32> position);

        i32 getCellIndex();
        void setCellIndex(i32 index);
        
        i32 getIndex();
        void setIndex(i32 newIndex);
};
#endif /* WAYPOINT_H */