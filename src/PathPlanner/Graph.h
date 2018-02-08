#ifndef GRAPH_H
#define GRAPH_H

#include "WayPoint.h"
#include "Edge.h"
#include <list>
#include <vector>
#include <map>
class Graph{
    public:
    // Vector containing all the nodes from the graph
        typedef std::vector<LWayPoint> nodeVector;
    // Alist containin all the edges grom the graph
        typedef std::list<Edge> edgeList;
    // A vector of list, each index of the vector indicates a node
    // and the list, the edges of that node
        typedef std::vector<edgeList> edgeListVector;
        
    private:
    // Graph instance
        static Graph* pinstance;
    // The nodes that form the graph
        nodeVector m_Nodes;
        edgeListVector m_Edges;
    // The edge list 
    // Indicates the next free position 
        int nextNode;
    // A map with the wayponts
        std::map< int, Vector2<float> > positionMap;
    // Iteratos
        std::list< Edge* >::iterator edgeIterator;
        std::vector< LWayPoint* >::iterator nodeIterator;
    public:
    // Constructor
        static Graph* Instance();
        Graph();
        ~Graph();
    // Returns the node at the given index
        LWayPoint& getNode(int idx);
    // Returns an edge
        Edge& getEdge(int from ,int to);
    // Retrieves the next free index
        int getNextIndex();
    // Adds a node to the graph and returns its index
        int addNode(LWayPoint node);
    // Removes a node by its index (set to invalid)
        void removeNode(int node);
    // Add and remove edges
        void addEdge(Edge edge);
        void removeEdge(int from, int to);
    // Returns the number of nodes in the graph
        int getNumNodes();
    // Returns the number of nodes in the graph
        int getNumEdges();
    // Returns if the graph is empty
        bool isEmpty();
    // Returns if the graph contains the node
        bool isPresent(int index);
    // Eucliden distance from 2 nodes
        float calculateDistance(Vector2<float> a, Vector2<float> b);
    // Clears the graph for new node insertions
        void Clear();
    // Getters
        nodeVector getNodeVector();
        edgeListVector getEdgeListVector();
        Vector2<float> getPositionFrom(int index);
    // Extra functions to load data 
        // To do
        //bool Load( char* fileName);
        //bool Load(std::ifstream& stream);
    // Iterators to acces nodes and edges
        //std::list< Edge* >::iterator getEdgeIterator(int node);
        //std::vector< LWayPoint* >::iterator getNodeIterator();
        //void incNodeIterator();
        //void incEdgeIterator();
        //bool nodeIteratorEnd();
        //bool edgeIteratorEnd();

};
#endif /*GRAPH_H*/