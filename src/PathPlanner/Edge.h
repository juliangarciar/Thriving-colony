#ifndef EDGE_h
#define EDGE_h

class Edge{
    protected:
    // Index of waypoint origin and end
        int m_iFrom;
        int m_iTo;
    // The weight of the edge
        float m_tCost;
    public:
    // Constructors
        Edge(int from, int to, float cost):m_iFrom(from),
                                           m_iTo(to),
                                           m_tCost(cost){}
        Edge(int from, int to):m_iFrom(from),
                               m_iTo(to),
                               m_tCost(1.0){}
        Edge():m_iFrom(-1),
               m_iTo(-1),
               m_tCost(1.0){}
        
        ~Edge();
    // Get/set parameters
        int getFrom();
        void setFrom(int newIndex);

        int getTo();
        void setTo(int newIndex);

        float getCost();
        void setCost(float newCost);
};
#endif /* EDGE_H */