#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "../GraphicEngine/Vector2.h"

#define INVALID_WP -1

class LWayPoint;
class NavNode{
    protected:
        int m_index;
    public:
        NavNode():m_index(INVALID_WP){}
        NavNode(int idx):m_index(idx){}
        ~NavNode();

        int getIndex();
        void setIndex(int newIndex);
};
class LWayPoint : public NavNode{
    protected:
        Vector2<float> m_vPosition;
    public:
        LWayPoint(Vector2<float> position);
        Vector2<float> getPosition();
        virtual ~LWayPoint();
};
#endif /* WAYPOINT_H */