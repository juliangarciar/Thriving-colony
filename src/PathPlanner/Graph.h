#ifndef GRAPH_H
#define GRAPH_H

#include "WayPoint.h"
#include "Edge.h"
#include <list>
#include <vector>
#include <map>
#include <Types.h>
#include <iostream>
class Graph{
    private:
    // The nodes that form the graph
        std::vector< LWayPoint > m_Nodes;
    // The edge list 
        std::vector< std::list< Edge > > m_Edges;
    // Self explanatory variables
        i32 mapX, mapY, nodeX, nodeY, nextNode, nWaypointsX, nWaypointsY;
    public:
    // Constructor
        Graph(i32 width, i32 height, i32 spaceX, i32 spaceY);
        ~Graph();
    // Init edges cost
        void initCost();
    // Load waypoints from file
        // Actually just loads a lot of waypoints
        void loadData();
    // Removes a node by its index (set to invalid)
        void removeNode(i32 node);
    // Add and remove edges
        void addEdge(Edge edge);
        void removeEdge(i32 from, i32 to);
    // Clears the graph for new node insertions
        void Clear();
    // Returns the node at the given index
        LWayPoint& getNode(i32 idx);
    // Returns an edge
        Edge& getEdge(i32 from ,i32 to);
    // Retrieves the next free index
        i32 getNextIndex();
    // Adds a node to the graph and returns its index
        i32 addNode(LWayPoint node);
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
    // Getters
        std::vector<LWayPoint> getNodeVector();
        std::list< Edge > getEdgeListVector(i32 index);
        std::list< Edge > getEdgeList(i32 index);

};
#endif /*GRAPH_H*/