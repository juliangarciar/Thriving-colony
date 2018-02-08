#ifndef EDGE_h
#define EDGE_h

#include <Types.h>

class Edge{
    protected:
    // Index of waypoint origin and end
        i32 m_iFrom;
        i32 m_iTo;
    // The weight of the edge
        f32 m_tCost;
    public:
    // Constructors
        Edge(i32 from, i32 to, f32 cost):m_iFrom(from),
                                           m_iTo(to),
                                           m_tCost(cost){}
        Edge(i32 from, i32 to):m_iFrom(from),
                               m_iTo(to),
                               m_tCost(1.0){}
        Edge():m_iFrom(-1),
               m_iTo(-1),
               m_tCost(1.0){}
        
        ~Edge();
    // Get/set parameters
        i32 getFrom();
        void setFrom(i32 newIndex);

        i32 getTo();
        void setTo(i32 newIndex);

        f32 getCost();
        void setCost(f32 newCost);
};
#endif /* EDGE_H */