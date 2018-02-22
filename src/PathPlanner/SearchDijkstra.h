#ifndef SEARCHDIJKSTRA_H
#define SEARCHDIJKSTRA_H

#include <MathEngine/Vector2.h>
#include "Graph.h"

class SearchDijkstra{
    private:
        Graph *m_Graph;
    // Indexed by node, contains the acumulative cost of that node
        std::vector<f32> m_GCosts;
    // Indexed by node, contains the cost from addin GCosts
        std::vector<f32> m_FCosts;

        std::vector< Edge* > m_shortestPathTree;
        std::vector< Edge* > m_searchFrontier;

        i32 m_iSource;
        i32 m_iTarget;
        f32 Calculate(i32 a, i32 b);
        void Search();
    public:
        SearchDijkstra(Graph* graph,
                        i32 source):m_Graph(graph), 
                                    m_FCosts(graph -> getNumNodes(), 0.0),
                                    m_GCosts(graph -> getNumNodes(), 0.0),
                                    m_shortestPathTree(graph -> getNumNodes()),
                                    m_searchFrontier(graph -> getNumNodes()),
                                    m_iSource(source)
        {
            Search();
        }
        ~SearchDijkstra();
        
        i32 getTarget();
};
#endif