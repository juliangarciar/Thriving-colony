#include "Graph.h"
Graph::~Graph(){
    
}
// Maybe is check if the index is present
 LWayPoint& Graph::getNode(int idx){
    return m_Nodes.at(idx);
}
// Maybe is check if the index is present
//LWayPoint& Graph::getNode(int idx){
//    return m_Nodes.at(idx);
//}
 Edge& Graph::getEdge(int from, int to){
    std::list<Edge> dummy = m_Edges.at(from);
    std::list<Edge>::iterator it = dummy.begin();
    while(it->getTo() != to){
        it++;
    }
    return *it;
}
//Edge& Graph::getEdge(int from, int to){
//    std::list<Edge> dummy = m_Edges.at(from);
//    std::list<Edge>::iterator it = dummy.begin();
//    while(it->getTo() != to){
//        it++;
//    }
//    return *it;
//}
int Graph::getNextIndex(){
    return nextNode;
}
// Maybe this will explode, check later
int Graph::addNode(LWayPoint node){
    int actual = nextNode;
    if(node.getIndex() != INVALID_WP)
        node.setIndex(nextNode);

    m_Edges.resize(nextNode + 1);
    m_Edges.at(nextNode) = std::list<Edge>();
    this->m_Nodes.push_back(node);
    this->nextNode++;
    return actual;
}
// Maybe check if the edge is viable
void Graph::removeNode(int node){
    getNode(node).setIndex(INVALID_WP);
}
// Maybe check if the edge is viable
void Graph::addEdge(Edge edge){
    if(edge.getFrom() != -1){
        Vector2<float> a = getNode(edge.getFrom()).getPosition();
        Vector2<float> b = getNode(edge.getTo()).getPosition();
        edge.setCost(calculateDistance(a, b));
        this->m_Edges.at(edge.getFrom()).push_back(edge);
    }
}
// Maybe check if from and to are available
void Graph::removeEdge(int from, int to){
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
int Graph::getNumNodes(){
    return m_Nodes.size();
}
int Graph::getNumEdges(){
    int count = 0;
    for ( int i = 0; i < m_Edges.size(); i++){
        count += m_Edges.at(i).size();
    }
    return count;
}
bool Graph::isEmpty(){
    return m_Nodes.empty();
}
bool Graph::isPresent(int index){
    if(m_Nodes.size() > index)
        return true;
    else    
        return false;
}
float Graph::calculateDistance(Vector2<float> a, Vector2<float> b){
    float dX = a.x - b.x;
    float dY = a.y - b.y;
    float distance = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
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

// Not implemented
//bool Graph::Load( char* fileName){
//}
// Not implemented
//bool Graph::Load(std::ifstream& stream){
//}