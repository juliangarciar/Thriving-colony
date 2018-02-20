#include "SearchAStar.h"
#include <WorldGeometry/MapMaster.h>
#include "PriorityQueue.h"

SearchAStar::~SearchAStar(){
    m_shortestPathTree.clear();
    m_searchFrontier.clear();
}
f32 SearchAStar::Calculate(i32 a, i32 b){
    f32 dX = m_Graph.getNode(a).getPosition().x - m_Graph.getNode(b).getPosition().x;
    f32 dY = m_Graph.getNode(a).getPosition().y - m_Graph.getNode(b).getPosition().y;
    f32 distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
    return distance;
}
void SearchAStar::Search(){
    // Fix this priority queue
    // Contiene ints, y su prioridad destack -> de de m_FCost
    IndexedPriorityQLow<float> pq(m_FCosts, m_Graph.getNumNodes());
    pq.insert(m_iSource);
    // Check if exist a direct vector to the target
    while(!pq.empty()){
        i32 NextClosestNode = pq.Pop();

        m_shortestPathTree[NextClosestNode] = m_searchFrontier[NextClosestNode];

        if(NextClosestNode == m_iTarget) {
            std::cout << "Objetivo encontrado \n";
            break;
        }

        // Fix this iterator
        // iterator of edges, given a node index

        // Change this
        //std::list<Edge> dummy = m_Graph.getEdgeListVector(NextClosestNode);
        std::list<Edge> dummy = MapMaster::Instance()->getValidatedEdges(NextClosestNode);
        std::list<Edge>::iterator it;

        //std::cout << "Tengo que ir al nodo " << m_iTarget << "\n";

        for(it = dummy.begin(); it != dummy.end(); it++){
            //Edge *stack = new Edge((*it).getFrom(), (*it).getTo(), (*it).getCost());
            Edge *stack = new Edge();
            stack -> setFrom((*it).getFrom());
            stack -> setTo((*it).getTo());
            stack -> setCost((*it).getCost());
            // Change this
            //MapMaster::Instance()->getGeometry()->checkCollisions(m_Graph.getNode(NextClosestNode).getPosition(), m_Graph.getNode(stack -> getTo()).getPosition());
            //MapMaster::Instance()->checkCollisions(NextClosestNode)
                float HCost = Calculate(m_iTarget, stack -> getTo());
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
std::list<i32> SearchAStar::getPathToTarget(){
    std::list<i32> path;

    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;    

    i32 nd = m_iTarget;
    path.push_front(nd);

    while ((nd != m_iSource) && ( m_searchFrontier[nd] != 0))
    {
        nd =  m_shortestPathTree[nd]->getFrom();

        path.push_front(nd);
    }
    path.push_front(m_iSource);
    return path;
}