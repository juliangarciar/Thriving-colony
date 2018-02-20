#include "Graph.h"

Graph::Graph(i32 width, i32 height, i32 spaceX, i32 spaceY){
    //mapGeometry = geometry;
    nextNode = 0;
    nodeX = spaceX;
    nodeY = spaceY;
    mapX = width;
    mapY = height;
    nWaypointsX = mapX / nodeX;
    nWaypointsY = mapY / nodeY;
    //m_Nodes = std::vector< WayPoint >(nWaypointsX * nWaypointsY);
    m_Edges = std::vector< std::list < Edge > >(nWaypointsX * nWaypointsY);
    //loadData();
    std::cout << "Inicializando waypoints \n";
    for(i32 z = 0; z < nWaypointsX * nWaypointsY; z++){
        std::list< Edge > tmp;
        m_Edges.at(z) = tmp;
    }
    for(i32 y = 0; y < nWaypointsY; y++){
        for(i32 x = 0; x < nWaypointsX; x++){
            std::cout << "Waypoint n: " << (y * nWaypointsY + x) << "\n";
            f32 dX = x * nodeX + nodeX / 2;
            f32 dY = y * nodeY + nodeY / 2;
            WayPoint dummy = WayPoint(Vector2<f32>(dX, dY));
            i32 reservedIndex = addNode(dummy);
            dummy.setIndex(reservedIndex);
            if(y == 0){
                if(x == 0){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() + 1);
                    b.setFrom(dummy.getIndex()), b.setTo(nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(nWaypointsX + 1);
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                }
                else if(x == nWaypointsX - 1){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(2 * dummy.getIndex() - 1);
                    c.setFrom(dummy.getIndex()), c.setTo(2 * dummy.getIndex());
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                    addEdge(d);
                    addEdge(e);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                }
                else if(x == nWaypointsX - 1){
                    Edge a = Edge();
                    Edge b = Edge();
                    Edge c = Edge();
                    a.setFrom(dummy.getIndex()), a.setTo(dummy.getIndex() - 1);
                    b.setFrom(dummy.getIndex()), b.setTo(dummy.getIndex() - nWaypointsX);
                    c.setFrom(dummy.getIndex()), c.setTo(dummy.getIndex() - nWaypointsX - 1);
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                    addEdge(d);
                    addEdge(e);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                    addEdge(d);
                    addEdge(e);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                    addEdge(d);
                    addEdge(e);
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
                    addEdge(a);
                    addEdge(b);
                    addEdge(c);
                    addEdge(d);
                    addEdge(e);
                    addEdge(f);
                    addEdge(g);
                    addEdge(h);
                }
            }
        }
    }
    std::cout << "Nwaypoints = " << m_Nodes.size() << std::endl;
    initCost();
}
void Graph::initCost(){
    std::list< Edge >::iterator it;
    for(i32 i = 0; i < getNumNodes(); i++){
        for(it = m_Edges.at(i).begin(); it != m_Edges.at(i).end(); it++){
            Vector2<f32> a = getNode(it->getFrom()).getPosition();
            Vector2<f32> b = getNode(it->getTo()).getPosition();
            it->setCost(calculateDistance(a, b));
        }
    }
}
Graph::~Graph(){
    
}

// Maybe check if the edge is viable
void Graph::removeNode(i32 node){
    getNode(node).setIndex(INVALID_WP);
}
// Maybe check if the edge is viable
void Graph::addEdge(Edge edge){
    if(edge.getFrom() != -1 && edge.getTo() != -1){
        m_Edges.at(edge.getFrom()).push_front(edge);
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
// Maybe is check if the index is present
WayPoint& Graph::getNode(i32 idx){
    return m_Nodes.at(idx);
}
Edge& Graph::getEdge(i32 from, i32 to){
    std::list<Edge> dummy = m_Edges.at(from);
    std::list<Edge>::iterator it = dummy.begin();
    while(it->getTo() != to){
        it++;
    }
    return *it;
}
i32 Graph::getNextIndex(){
    return nextNode;
}
// Maybe this will explode, check later
i32 Graph::addNode(WayPoint node){
    i32 actual = nextNode;
    std::cout << actual << "\n";
    node.setIndex(actual);
    m_Nodes.push_back(node);
    nextNode++;
    return actual;
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
std::vector< WayPoint > Graph::getNodeVector(){
    return m_Nodes;
}
std::list< Edge > Graph::getEdgeListVector(i32 index){
    std::list< Edge > dummy;
    if(index > -1 && index < getNumNodes())
        dummy = m_Edges.at(index);

    return dummy;
}
