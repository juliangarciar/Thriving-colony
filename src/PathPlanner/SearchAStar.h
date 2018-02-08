#ifndef SEARCHASTAR_H
#define SEARCHASTAR_H

#include "Graph.h"
#include "../GraphicEngine/Vector2.h"
#include <queue>
#include <iterator>
#include <Types.h>

class SearchAStar{
    private:
        
        Graph& m_Graph;
    // Indexed by node, contains the acumulative cost of that node
        std::vector<f32> m_GCosts;
    // Indexed by node, contains the cost from addin GCosts
        std::vector<f32> m_FCosts;

        std::vector< Edge* > m_shortestPathTree;
        std::vector< Edge* > m_searchFrontier;
        std::vector<i32>  m_Route;

        i32 m_iSource;
        i32 m_iTarget;
    // The A* search algorithm
        void Search();
    // Comparator for priority queue
        struct comparePriority
        {
            comparePriority(std::vector<f32> data):costs(data){}
            std::vector<f32> costs;
            bool operator()(i32& a, i32& b) const
            {
                return costs.at(a) < costs.at(b);
            }
        };
    public:
        SearchAStar(Graph& graph,
                        i32 source,
                        i32 target):m_Graph(graph), 
                                    m_GCosts(graph.getNumNodes(), 0.0),
                                    m_FCosts(graph.getNumNodes(), 0.0),
                                    m_shortestPathTree(graph.getNumNodes()),
                                    m_searchFrontier(graph.getNumNodes()),
                                    m_iSource(source),
                                    m_iTarget(target)
                                    
                                    
        {
            Search();
        }
        ~SearchAStar();
    // Returns the vector of edges that the algorithm has examined
        //std::vector< Edge*> GetSPT();
    // Returns a vector of node indexes that comprise the shortest path
        std::list<i32> getPathToTarget();
    // Returns the total cost to the target
        //f32 getCost();
    // Calculates the heuristic cost from node 'a' to node 'b'
        f32 Calculate(i32 a, i32 b);
};
#endif /* SEARCHASTAR_H */