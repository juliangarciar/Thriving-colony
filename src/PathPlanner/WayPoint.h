#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <Types.h>
#include <MathEngine/Vector2.h>

#define INVALID_WP -1
class WayPoint{
    private:
        i32 m_index;
        i32 cellIndex;
        Vector2<f32> m_vPosition;
    public:
        WayPoint();
        WayPoint(Vector2<f32> position);
        ~WayPoint();
    // Get / setters
        Vector2<f32> getPosition();
        void setPosition(Vector2<f32> position);

        i32 getCellIndex();
        void setCellIndex(i32 index);
        
        i32 getIndex();
        void setIndex(i32 newIndex);
};
#endif /* WAYPOINT_H */