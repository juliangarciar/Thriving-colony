#ifndef GRAPH_H
#define GRAPH_H

#include "WayPoint.h"
#include "Edge.h"
#include <list>
#include <vector>
#include <map>
#include <Types.h>

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
        i32 nextNode;
    // A map with the wayponts
        std::map< i32, Vector2<f32> > positionMap;
    // Iteratos
        std::list< Edge* >::iterator edgeIterator;
        std::vector< LWayPoint* >::iterator nodeIterator;
    public:
    // Constructor
        static Graph* Instance();
        Graph();
        ~Graph();
    // Returns the node at the given index
        LWayPoint& getNode(i32 idx);
    // Returns an edge
        Edge& getEdge(i32 from ,i32 to);
    // Retrieves the next free index
        i32 getNextIndex();
    // Adds a node to the graph and returns its index
        i32 addNode(LWayPoint node);
    // Removes a node by its index (set to invalid)
        void removeNode(i32 node);
    // Add and remove edges
        void addEdge(Edge edge);
        void removeEdge(i32 from, i32 to);
    // Returns the number of nodes in the graph
        i32 getNumNodes();
    // Returns the number of nodes in the graph
        i32 getNumEdges();
    // Returns if the graph is empty
        bool isEmpty();
    // Returns if the graph contains the node
        bool isPresent(i32 index);
    // Eucliden distance from 2 nodes
        f32 calculateDistance(Vector2<f32> a, Vector2<f32> b);
    // Clears the graph for new node insertions
        void Clear();
    // Getters
        nodeVector getNodeVector();
        edgeListVector getEdgeListVector();
        Vector2<f32> getPositionFrom(i32 index);
    // Extra functions to load data 
        // To do
        //bool Load( char* fileName);
        //bool Load(std::ifstream& stream);
    // Iterators to acces nodes and edges
        //std::list< Edge* >::iterator getEdgeIterator(i32 node);
        //std::vector< LWayPoint* >::iterator getNodeIterator();
        //void incNodeIterator();
        //void incEdgeIterator();
        //bool nodeIteratorEnd();
        //bool edgeIteratorEnd();

};
#endif /*GRAPH_H*/