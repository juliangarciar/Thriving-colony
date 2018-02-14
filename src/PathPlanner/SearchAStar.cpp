#include "SearchAStar.h"
#include "../WorldGeometry/CellSpacePartition.h"
#include "PriorityQueue.h"

SearchAStar::~SearchAStar(){
    this->m_shortestPathTree.clear();
    this->m_searchFrontier.clear();
}
f32 SearchAStar::Calculate(i32 a, i32 b){
    f32 dX = m_Graph.getNode(a).getPosition().x - m_Graph.getNode(b).getPosition().x;
    f32 dY = m_Graph.getNode(a).getPosition().y - m_Graph.getNode(b).getPosition().y;
    f32 distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
    return distance;
}
void SearchAStar::Search(){
    // Fix this priority queue
    // Contiene ints, y su prioridad depende de m_FCost
    //std::priority_queue<i32, std::vector<i32>, comparePriority> pq(m_FCosts);
    IndexedPriorityQLow<float> pq(m_FCosts, m_Graph.getNumNodes());
    //pq.push(m_iSource);
    pq.insert(m_iSource);
    // Check if exist a direct vector to the target
    while(!pq.empty()){
        i32 NextClosestNode = pq.Pop();
        //i32 NextClosestNode = pq.top();
        //pq.pop();
        m_shortestPathTree[NextClosestNode] = m_searchFrontier[NextClosestNode];
        if(NextClosestNode == m_iTarget) {
            std::cout << "Objetivo encontrado \n";
            break;
        }
       

        // Fix this iterator
        // iterator of edges, given a node index
        std::list<Edge> dummy = m_Graph.getEdgeListVector(NextClosestNode);
        std::cout << dummy.size() << "\n";
        std::list<Edge>::iterator edgeIterator = dummy.begin();
        for( Edge* pE = &(*edgeIterator);
            edgeIterator != dummy.end();
            edgeIterator++)
        {
            //if(!CellSpacePartition::Instance() -> checkCollisions(m_Graph.getNode(NextClosestNode).getPosition(), m_Graph.getNode(pE -> getTo()).getPosition())){
                double HCost = Calculate(m_iTarget, pE->getTo());

                double GCost = m_GCosts[NextClosestNode] + pE->getCost();

                if(m_searchFrontier[pE->getTo()] == NULL){
                    m_FCosts[pE->getTo()] = GCost + HCost;
                    m_GCosts[pE->getTo()] = GCost;

                    //pq.push(pE->getTo());
                    pq.insert(pE -> getTo());
                    m_searchFrontier[pE->getTo()] = pE;
                }
                else if((GCost < m_GCosts[pE->getTo()]) && (m_shortestPathTree[pE->getTo()] == NULL)){
                    m_FCosts[pE->getTo()] = GCost + HCost;
                    m_GCosts[pE->getTo()] = GCost;

                    // The fuck is this
                    pq.ChangePriority(pE->getTo());
                    m_searchFrontier[pE->getTo()] = pE;
                }
            //}
        }
    }
}
std::list<i32> SearchAStar::getPathToTarget(){
    std::list<i32> path;

    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;    

    i32 nd = m_iTarget;

    path.push_front(nd);
    
    while ((nd != m_iSource) && (m_shortestPathTree[nd] != 0))
    {
        std::cout << "Recorriendo shorthesPathTree \n";
        nd = m_shortestPathTree[nd]->getFrom();

        path.push_front(nd);
    }
    path.push_front(m_iSource);
    return path;
}