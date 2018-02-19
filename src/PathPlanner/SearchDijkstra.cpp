#include "SearchDijkstra.h"
#include "../WorldGeometry/CellSpacePartition.h"
#include "PriorityQueue.h"
f32 SearchDijkstra::Calculate(i32 a, i32 b){
    f32 dX = m_Graph -> getNode(a).getPosition().x - m_Graph -> getNode(b).getPosition().x;
    f32 dY = m_Graph -> getNode(a).getPosition().y - m_Graph -> getNode(b).getPosition().y;
    f32 distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
    return distance;
}
SearchDijkstra::~SearchDijkstra(){

}
void SearchDijkstra::Search(){
    IndexedPriorityQLow<float> pq(m_FCosts, m_Graph -> getNumNodes());
    pq.insert(m_iSource);
    // Check if exist a direct vector to the target
    while(!pq.empty()){
        i32 NextClosestNode = pq.Pop();

        m_shortestPathTree[NextClosestNode] = m_searchFrontier[NextClosestNode];

        if(m_Graph -> getNode(NextClosestNode).entities.empty()) {
            m_iTarget = NextClosestNode;
            break;
        }

        // Fix this iterator
        // iterator of edges, given a node index
        std::list<Edge> dummy = m_Graph -> getEdgeList(NextClosestNode);
        std::list<Edge>::iterator it;


        for(it = dummy.begin(); it != dummy.end(); it++){
            Edge *stack = new Edge();
            stack -> setFrom((*it).getFrom());
            stack -> setTo((*it).getTo());
            stack -> setCost((*it).getCost());
            CellSpacePartition::Instance() -> checkCollisions(m_Graph -> getNode(NextClosestNode).getPosition(), m_Graph -> getNode(stack -> getTo()).getPosition());
            float HCost = Calculate(m_iSource, stack -> getTo());
            float GCost = m_GCosts[NextClosestNode] + stack -> getCost();
            //std::cout << "Distancia H: " << HCost << "\n";
            //std::cout << "Distancia G: " << GCost << "\n";
            if(m_searchFrontier[stack -> getTo()] == NULL){
                m_FCosts[stack -> getTo()] = GCost + HCost;
                m_GCosts[stack -> getTo()] = GCost;

                pq.insert(stack -> getTo());
                m_searchFrontier[stack -> getTo()] = stack;
            }
            else if((GCost < m_GCosts[stack -> getTo()]) && (m_shortestPathTree[stack -> getTo()] == NULL)){
                m_FCosts[stack -> getTo()] = GCost + HCost;
                m_GCosts[stack -> getTo()] = GCost;

                m_searchFrontier[stack -> getTo()] = stack;
            }
        }
    }
}
i32 SearchDijkstra::getTarget(){
    return m_iTarget;
}