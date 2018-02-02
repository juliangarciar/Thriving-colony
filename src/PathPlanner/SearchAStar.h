#ifndef SEARCHASTAR_H
#define SEARCHASTAR_H

#include "Graph.h"
#include "../GraphicEngine/Vector2.h"
#include <queue>
#include <iterator>
class SearchAStar{
    private:
        
        Graph& m_Graph;
    // Indexed by node, contains the acumulative cost of that node
        std::vector<float> m_GCosts;
    // Indexed by node, contains the cost from addin GCosts
        std::vector<float> m_FCosts;

        std::vector< Edge* > m_shortestPathTree;
        std::vector< Edge* > m_searchFrontier;
        std::vector<int>  m_Route;

        int m_iSource;
        int m_iTarget;
    // The A* search algorithm
        void Search();
    // Comparator for priority queue
        struct comparePriority
        {
            comparePriority(std::vector<float> data):costs(data){}
            std::vector<float> costs;
            bool operator()(int& a, int& b) const
            {
                return costs.at(a) < costs.at(b);
            }
            
        };
    public:
        SearchAStar(Graph& graph,
                        int source,
                        int target):m_Graph(graph), 
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
        std::list<int> getPathToTarget();
    // Returns the total cost to the target
        //float getCost();
    // Calculates the heuristic cost from node 'a' to node 'b'
        float Calculate(int a, int b);
};
#endif /* SEARCHASTAR_H */