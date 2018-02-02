#include "SearchAStar.h"
SearchAStar::~SearchAStar(){
    this->m_shortestPathTree.clear();
    this->m_searchFrontier.clear();
}
float SearchAStar::Calculate(int a, int b){
    float dX = m_Graph.getNode(a).getPosition().x - m_Graph.getNode(b).getPosition().x;
    float dY = m_Graph.getNode(a).getPosition().y - m_Graph.getNode(b).getPosition().y;
    float distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
    return distance;
}
void SearchAStar::Search(){
    // Fix this priority queue
    // Contiene ints, y su prioridad depende de m_FCost
    std::priority_queue<int, std::vector<int>, comparePriority> pq(m_FCosts);
    pq.push(m_iSource);

    while(!pq.empty()){
        int NextClosestNode = pq.top();
        pq.pop();
        m_shortestPathTree[NextClosestNode] = m_searchFrontier[NextClosestNode];
        if(NextClosestNode == m_iTarget) return;

        // Fix this iterator
        // iterator of edges, given a node index
        std::list<Edge, std::allocator<Edge> > dummy = m_Graph.getEdgeListVector().at(NextClosestNode);
        std::list<Edge>::iterator edgeIterator(dummy.begin());

        for( Edge* pE = &(*edgeIterator);
            edgeIterator != dummy.end();
            edgeIterator++)
        {
            double HCost = Calculate(m_iTarget, pE->getTo());

            double GCost = m_GCosts[NextClosestNode] + pE->getCost();

            if(m_searchFrontier[pE->getTo()] == NULL){
                m_FCosts[pE->getTo()] = GCost + HCost;
                m_GCosts[pE->getTo()] = GCost;

                pq.push(pE->getTo());

                m_searchFrontier[pE->getTo()] = pE;
            }
            else if((GCost < m_GCosts[pE->getTo()]) && (m_shortestPathTree[pE->getTo()] == NULL)){
                m_FCosts[pE->getTo()] = GCost + HCost;
                m_GCosts[pE->getTo()] = GCost;

                // The fuck is this
                //pq->ChangePriority(pE->getTo());
                m_searchFrontier[pE->getTo()] = pE;
            }
        }
    }
}
std::list<int> SearchAStar::getPathToTarget(){
    std::list<int> path;

    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;    

    int nd = m_iTarget;

    path.push_front(nd);
        
    while ((nd != m_iSource) && (m_shortestPathTree[nd] != 0))
    {
        nd = m_shortestPathTree[nd]->getFrom();

        path.push_front(nd);
    }
    path.push_front(m_iSource);
    return path;
}