// Operation System: OSX El Capitan Version 10.11.6
// C++ Framework: XCode Version 8.0 (8A218a)
// Compilation: Yes
// Running: Yes


//
//  main.cpp
//  fish-5c-graphs
//
//  Created by Oliver Fishstein on 11/20/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

// stl
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

// boost
#include <boost/graph/adjacency_list.hpp>

// class headers
#include "d_except.h"
#include "d_matrix.h"
#include "heapV.h"

using namespace std;
using namespace boost;

//#define LargeValue 99999999;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int, int> cell; // cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
};

//  struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef std::pair<Graph::edge_iterator, Graph::edge_iterator> EdgePair;


// functions

// clear marked vertices
void clearMarked(Graph &g)
{
    // set up iterators
    Graph::vertex_iterator vertexIterator, vertexEnd;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vertices
    while (vertexIterator != vertexEnd)
    {
        // set false and iterate
        g[*vertexIterator].marked = false;
        ++vertexIterator;
        
    }
}

// clear visited vertices
void clearVisited(Graph &g)
{
    // set up iterators
    Graph::vertex_iterator vertexIterator, vertexEnd;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vertices
    while (vertexIterator != vertexEnd)
    {
        // set false and iterate
        g[*vertexIterator].visited = false;
        ++vertexIterator;
    }
}

// finds an edge
Graph::edge_descriptor findEdge(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
    EdgePair edgePair;
    
    // iterate through edge pairs
    for (edgePair = edges(g); edgePair.first != edgePair.second; ++edgePair.first)
    {
        // get the two vertices that are joined by this edge
        if (source(*edgePair.first, g) == u && target(*edgePair.first, g) == v)
        {
            return *edgePair.first;
        }
    }
    
    // return edge pair
    return *edgePair.first;
}

// depth first search
int depthFirst(Graph &g, Graph::vertex_descriptor v)
{
    int c = 0;
    
    if (!g[v].visited)
    {
        // mark vertex visited
        g[v].visited = true;
        c = 1;
        
        // set up iterators
        Graph::adjacency_iterator neighbourIterator, neighbourEnd;
        tie(neighbourIterator, neighbourEnd) = adjacent_vertices(v, g);
        
        // iterate through neighbors
        while (neighbourIterator != neighbourEnd)
        {
            // add to count
            c += depthFirst(g, *neighbourIterator);
            
            // increment
            ++neighbourIterator;
        }
    }
    
    return c;
}

// determines if all vertices are reachable
bool allReachable(Graph::vertex_descriptor v, Graph &g)
{
    int numVisited = 0;
    clearVisited(g);
    
    // get visited count
    numVisited = depthFirst(g, v);
    
    // if number of vertices and num visted are equal
    return numVisited == num_vertices(g);
    
}

// relax for Bellman Ford
void relaxBF(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
    if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight)
    {
        g[v].weight = g[findEdge(g, u, v)].weight + g[u].weight;
        g[v].pred = u;
    }
}

// relax for Dijkstra
bool relaxDijkstra(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
    if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight )
    {
        if (g[findEdge(g, u, v)].weight < 0)
        {
            return false;
        }
        
        g[v].weight = g[findEdge(g, u, v)].weight + g[u].weight;
        g[v].pred = u;
    }
    
    return true;
}


// dijkstras algorithm
bool dijkstra(Graph &g, Graph::vertex_descriptor s)
{
    //set all distances to inf
    Graph::vertex_iterator vertexIterator, vertexEnd;
    Graph::edge_iterator edgeIterator, edgeEnd;
    std::stack<Graph::vertex_descriptor> stack;
    heapV <Graph::vertex_descriptor, Graph> heapGraph;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vetexes
    while (vertexIterator != vertexEnd)
    {
        // set weight and pred and add to heap
        g[*vertexIterator].weight = LargeValue;
        g[*vertexIterator].pred = -99999;
        heapGraph.minHeapInsert(*vertexIterator, g);
        
        // increment
        ++vertexIterator;
    }
    
    g[s].weight = 0;
    
    // while heap isn't empty
    while (heapGraph.size() != 0)
    {
        Graph::vertex_descriptor u = heapGraph.extractMinHeapMinimum(g);
        stack.push(u);
        Graph::adjacency_iterator neighbourIterator, neighbourEnd;
        tie(neighbourIterator, neighbourEnd) = adjacent_vertices(u, g);
        
        // iterate though neighbors
        while (neighbourIterator != neighbourEnd)
        {
            // check if neg edge and leave
            if (!relaxDijkstra(g, u, *neighbourIterator))
            {
                cout << "Negative Edge in Dijkstra Quiting\n";
                
                return false;
            }
            
            // build min heap
            heapGraph.buildMinHeap(heapGraph.size(), g);
            ++neighbourIterator;
        }
    }
    
    // return if all reachable
    return allReachable(s,g);
    
}

// bellman ford algorithm
bool bellmanFord(Graph &g, Graph::vertex_descriptor s)
{
    //set all distances to inf
    Graph::vertex_iterator vertexIterator, vertexEnd;
    Graph::edge_iterator edgeIterator, edgeEnd;
    
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate though vertixes
    while (vertexIterator != vertexEnd)
    {
        g[*vertexIterator].weight = LargeValue;
        g[*vertexIterator].pred = -99999;
        
        ++vertexIterator;
    }
    
    g[s].weight = 0;
    
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // go through vertices - 1
    for (size_t i = 1; i < num_vertices(g) - 1; i++)
    {
        tie(edgeIterator, edgeEnd) = edges(g);
        
        // iterate though edges
        while (edgeIterator != edgeEnd)
        {
            Graph::vertex_descriptor u = source(*edgeIterator, g);
            Graph::vertex_descriptor v = target(*edgeIterator, g);
            
            relaxBF(g, u, v);
            
            ++edgeIterator;
        }
    }
    
    tie(edgeIterator, edgeEnd) = edges(g);
    
    // iterate through edges
    while (edgeIterator != edgeEnd)
    {
        Graph::vertex_descriptor u = source(*edgeIterator, g);
        Graph::vertex_descriptor v = target(*edgeIterator, g);
        
        if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight)
        {
            return false;
        }
        
        ++edgeIterator;
    }
    
    return true;
}


// given function from assignment
void initializeGraph(Graph &g,
                     Graph::vertex_descriptor &start,
                     Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    int startIndex, endIndex;
    fin >> n;
    fin >> startIndex >> endIndex;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        
        v = add_vertex(g);
        if (i == startIndex)
        {
            start = v;
        }
        if (i == endIndex)
        {
            end = v;
        }
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        add_edge(i, j, e, g);
    }
    
    clearMarked(g);
    clearVisited(g);
}

// main
int main()
{
    ifstream fin;
    string fileName;
    
    // get filename for graph
    cout << "Enter filename: " << endl;
    cin >> fileName;
    
    fin.open(fileName.c_str());
    
    // check if opens
    if (!fin)
    {
        cerr << "ERROR: Can't open " << fileName << endl;
        exit(1);
    }
    
    // vars for bellman ford
    Graph gBF;
    Graph::vertex_descriptor startBF, endBF, currentPosBF;
    
    // init graph
    initializeGraph(gBF, startBF, endBF, fin);
    
    cout << "\nBellman-Ford:\n";
    fin.close();
    
    // run bellmanFord
    if (bellmanFord(gBF, startBF))
    {
        // if success
        cout << "No negative loops\n";
        cout << "Total cost = " << gBF[endBF].weight << endl;
    }
    else
    {
        // if failure
        cout << "Negative loops found\n";
        cout << "Total cost = -infinity"<< endl;
    }
    
    // print results
    if (gBF[endBF].pred == -99999)
    {
        // no path
        cout << "No shortest path exists\n";
    }
    else
    {
        // print shortest path
        currentPosBF = endBF;
        clearMarked(gBF);
        cout << "Start [" << startBF << "]\n";
        cout << "End [" << endBF << "]\n";
        
        // print each node in path
        while (currentPosBF != startBF)
        {
            cout<<"["<<currentPosBF<< "]  ";
            
            if (gBF[currentPosBF].marked)
            {
                cout << "FOUND LOOP\n";
                break;
            }
            
            gBF[currentPosBF].marked = true;
            currentPosBF = gBF[currentPosBF].pred;
        }
        
        cout << "[" << currentPosBF << "] \n";
    }
    
    // vars for dijkstra
    Graph gD;
    Graph::vertex_descriptor startD, endD, currentPosD;
    fin.open(fileName.c_str());
    
    // check if file opens
    if (!fin)
    {
        cerr << "ERROR: Can't open " << fileName << endl;
        exit(1);
    }
    
    // init graph
    initializeGraph(gD, startD, endD, fin);
    
    cout << "\nDijkstra:\n";
    fin.close();
    
    // run dijkstra
    if (dijkstra(gD, startD))
    {
        // if success
        cout << "Connected \n";
    }
    else
    {
        // if not success
        cout << "Not connected\n";
    }
    // print results
    if (gD[endD].pred == -99999)
    {
        // no path
        cout << "No shortest path exists\n";
    }
    else
    {
        // print shortest path
        currentPosD = endD;
        cout << "Total cost = " << gD[currentPosD].weight << endl;
        cout << "Start [" << startD << "]\n";
        cout << "End [" << endD << "]\n";
        
        // print each node in path
        while (currentPosD != startD)
        {
            cout << "[" << currentPosD << "]  ";
            currentPosD = gD[currentPosD].pred;
            
        }
        cout << "[" << currentPosD << "] \n";
    }
    
    return 0;
}
