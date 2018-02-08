#include "Graph.h"
#define GRID 100
#define K 9000
Graph* Graph::pinstance = 0;

Graph* Graph::Instance() {
    if(pinstance == 0) {
        pinstance = new Graph();
    }
    return pinstance;
}
Graph::Graph(){
    this->nextNode = 0;
    this->m_Nodes = nodeVector();
    this->m_Edges = edgeListVector();

// Lots of waypoints -> debugging purpose
    i32 nWaypointsX, nWaypointsY;
    nWaypointsX = K / GRID;
    nWaypointsY = K / GRID;
    for(i32 y = 0; y < nWaypointsY; y++){
        for(i32 x = 0; x < nWaypointsX; x++){
            f32 dX = x * GRID + GRID / 2;
            f32 dY = y * GRID + GRID / 2;
            LWayPoint dummy = LWayPoint(Vector2<f32>(dX, dY));
            this->addNode(dummy);
            if(y == 0){
                if(x == 0){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() + 1);
                    b.setFrom(dummy.getIndex()), b.setTo(nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(nWaypointsX + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                }
                else if(x == nWaypointsX - 1){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(2 * dummy.getIndex() - 1);
                    c.setFrom(dummy.getIndex()), c.setTo(2 * dummy.getIndex());
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                }
                else{
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    Edge d = Edge();
                    Edge e = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() + 1);
                    c.setFrom(dummy.getIndex()), c.setTo(2 * dummy.getIndex() - 1);
                    d.setFrom(dummy.getIndex()), d.setTo(2 * dummy.getIndex());
                    e.setFrom(dummy.getIndex()), e.setTo(2 * dummy.getIndex() + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                    this->addEdge(d);
                    this->addEdge(e);
                }
            }
            else if(y == nWaypointsY - 1){
                if(x == 0){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() + 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - nWaypointsX + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                }
                else if(x == nWaypointsX - 1){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - nWaypointsX - 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                }
                else{
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    Edge d = Edge();
                    Edge e = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() + 1);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - nWaypointsX - 1);
                    d.setFrom(dummy.getIndex()), d.setTo(dummy.getIndex() - nWaypointsX);
                    e.setFrom(dummy.getIndex()), e.setTo(dummy.getIndex() - nWaypointsX + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                    this->addEdge(d);
                    this->addEdge(e);
                }
            }
            else{
                if(x == 0){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    Edge d = Edge();
                    Edge e = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - nWaypointsX);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX + 1);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() + 1);
                    d.setFrom(dummy.getIndex()), d.setTo(dummy.getIndex() + nWaypointsX);
                    e.setFrom(dummy.getIndex()), e.setTo(dummy.getIndex() + nWaypointsX + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                    this->addEdge(d);
                    this->addEdge(e);
                }
                else if(x == nWaypointsX - 1){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    Edge d = Edge();
                    Edge e = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - nWaypointsX - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - 1);
                    d.setFrom(dummy.getIndex()), d.setTo(dummy.getIndex() + nWaypointsX - 1);
                    e.setFrom(dummy.getIndex()), e.setTo(dummy.getIndex() + nWaypointsX);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                    this->addEdge(d);
                    this->addEdge(e);
                }
                else{
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    Edge d = Edge();
                    Edge e = Edge();
                    Edge f = Edge();
                    Edge g = Edge();
                    Edge h = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - nWaypointsX - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - nWaypointsX + 1);
                    d.setFrom(dummy.getIndex()), d.setTo(dummy.getIndex() - 1);
                    e.setFrom(dummy.getIndex()), e.setTo(dummy.getIndex() + 1);
                    f.setFrom(dummy.getIndex()), f.setTo(dummy.getIndex() + nWaypointsX - 1);
                    g.setFrom(dummy.getIndex()), g.setTo(dummy.getIndex() + nWaypointsX);
                    h.setFrom(dummy.getIndex()), h.setTo(dummy.getIndex() + nWaypointsX + 1);
                    this->addEdge(a);
                    this->addEdge(b);
                    this->addEdge(c);
                    this->addEdge(d);
                    this->addEdge(e);
                    this->addEdge(f);
                    this->addEdge(g);
                    this->addEdge(h);
                }
            }
        }
    }
}
Graph::~Graph(){
    
}
// Maybe is check if the index is present
 LWayPoint& Graph::getNode(i32 idx){
    return m_Nodes.at(idx);
}
// Maybe is check if the index is present
//LWayPoint& Graph::getNode(i32 idx){
//    return m_Nodes.at(idx);
//}
 Edge& Graph::getEdge(i32 from, i32 to){
    std::list<Edge> dummy = m_Edges.at(from);
    std::list<Edge>::iterator it = dummy.begin();
    while(it->getTo() != to){
        it++;
    }
    return *it;
}
//Edge& Graph::getEdge(i32 from, i32 to){
//    std::list<Edge> dummy = m_Edges.at(from);
//    std::list<Edge>::iterator it = dummy.begin();
//    while(it->getTo() != to){
//        it++;
//    }
//    return *it;
//}
i32 Graph::getNextIndex(){
    return nextNode;
}
// Maybe this will explode, check later
i32 Graph::addNode(LWayPoint node){
    i32 actual = nextNode;
    if(node.getIndex() != INVALID_WP)
        node.setIndex(nextNode);

    positionMap.insert(std::pair<i32, Vector2<f32> >(nextNode, node.getPosition()));

    m_Edges.resize(nextNode + 1);
    m_Edges.at(nextNode) = std::list<Edge>();
    this->m_Nodes.push_back(node);
    this->nextNode++;
    return actual;
}
// Maybe check if the edge is viable
void Graph::removeNode(i32 node){
    getNode(node).setIndex(INVALID_WP);
}
// Maybe check if the edge is viable
void Graph::addEdge(Edge edge){
    if(edge.getFrom() != -1){
        Vector2<f32> a = getNode(edge.getFrom()).getPosition();
        Vector2<f32> b = getNode(edge.getTo()).getPosition();
        edge.setCost(calculateDistance(a, b));
        this->m_Edges.at(edge.getFrom()).push_back(edge);
    }
}
// Maybe check if from and to are available
void Graph::removeEdge(i32 from, i32 to){
    // Erase the edge from -> to
    std::list<Edge> dummy = m_Edges.at(from);
    std::list<Edge>::iterator it = dummy.begin();
    while(it->getTo() != to){
        it++;
    }
    m_Edges.at(from).erase(it);
    // Erase the edge to -> from
    dummy = m_Edges.at(to);
    it = dummy.begin();
    while(it->getFrom() != from){
        it++;
    }
    m_Edges.at(to).erase(it);
}
i32 Graph::getNumNodes(){
    return m_Nodes.size();
}
i32 Graph::getNumEdges(){
    i32 count = 0;
    for ( i32 i = 0; i < m_Edges.size(); i++){
        count += m_Edges.at(i).size();
    }
    return count;
}
bool Graph::isEmpty(){
    return m_Nodes.empty();
}
bool Graph::isPresent(i32 index){
    if(m_Nodes.size() > index)
        return true;
    else    
        return false;
}
f32 Graph::calculateDistance(Vector2<f32> a, Vector2<f32> b){
    f32 dX = a.x - b.x;
    f32 dY = a.y - b.y;
    f32 distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
    return distance;
}
void Graph::Clear(){
    m_Nodes.clear();
    m_Edges.clear();
    nextNode = 0;
}
Graph::nodeVector Graph::getNodeVector(){
    return m_Nodes;
}
Graph::edgeListVector Graph::getEdgeListVector(){
    return m_Edges;
}
Vector2<f32> Graph::getPositionFrom(i32 index){
    return this->positionMap.find(index)->second;
}
// Not implemented
//bool Graph::Load( char* fileName){
//}
// Not implemented
//bool Graph::Load(std::ifstream& stream){
//}
//std::list< Edge* >::iterator Graph::getEdgeIterator(i32 node){
//    edgeIterator = std::list< Edge >::iterator(m_Edges.at(node).begin());
//    return &edgeIterator;
//}
//std::vector< LWayPoint* >::iterator Graph::getNodeIterator(){
//    nodeIterator(m_Nodes.begin());
//    return &nodeIterator;
//}
//void Graph::incNodeIterator(){
//    nodeIterator++;
//}
//void Graph::incEdgeIterator(){
//    edgeIterator++;
//}
//bool Graph::nodeIteratorEnd(){
//    if(nodeIterator == m_Nodes.end())
//        return true;
//    else
//        return false;
//}
//bool Graph::edgeIteratorEnd(){
//    if(edgeIterator == m_Nodes.end())
//        return true;
//    else
//        return false;
//}