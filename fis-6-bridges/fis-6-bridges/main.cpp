// Operation System: OSX El Capitan Version 10.11.6
// C++ Framework: XCode Version 8.0 (8A218a)
// Compilation: Yes
// Running: Yes


//
//  main.cpp
//  fis-6-bridges
//
//  Created by Oliver Fishstein on 12/5/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>

#include "d_except.h"
#include "d_matrix.h"
#include "heapV.h"

using namespace std;
using namespace boost;

#define LargeValue 99999999;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int, int> cell;
    Graph::vertex_descriptor pred;
    int weight;
    bool visited;
    bool marked;
};

// create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef std::pair<Graph::edge_iterator, Graph::edge_iterator> EdgePair;

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

// initialize g using data from file input
void initializeGraph(Graph &g,
                     Graph::vertex_descriptor &start,
                     Graph::vertex_descriptor &end, ifstream &fin)
{
    EdgeProperties e;
    int n, i, j;
    
    fin >> n;

    Graph::vertex_descriptor v;
    
    // add nodes
    for (int i = 0; i < n; i++)
    {
        // add vertex
        v = add_vertex(g);
    }
    
    // while file is not done
    while (fin.peek() != '.')
    {
        // get info and add edge
        fin >> i >> j >> e.weight;
        add_edge(i, j, e, g);
    }
    
    // clear marked and visited
    clearMarked(g);
    clearVisited(g);
}

// depth first search
int depthFirst(Graph &g, Graph::vertex_descriptor v)
{
    int count = 0;
    
    if (!g[v].visited)
    {
        // mark vertex visited
        g[v].visited = true;
        count = 1;
        
        // set up iterators
        Graph::adjacency_iterator neighbourIterator, neighbourEnd;
        tie(neighbourIterator, neighbourEnd) = adjacent_vertices(v, g);
        
        // iterate through neighbors
        while (neighbourIterator != neighbourEnd)
        {
            // add to count
            count += depthFirst(g, *neighbourIterator);
            
            // increment
            ++neighbourIterator;
        }
    }
    
    return count;
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

// returns if the graph g is connected
bool isConnected(Graph &g)
{
    return allReachable(0, g);
}

// helps the cycle function
bool cycleHelper(Graph &g, Graph::vertex_descriptor v)
{
    // if visited
    if (g[v].visited)
    {
        // return true
        return true;
    }
    else
    {
        // set visited
        g[v].visited = true;
        
        // set up iterator
        Graph::adjacency_iterator neighbourIterator, neighbourEnd;
        tie(neighbourIterator, neighbourEnd) = adjacent_vertices(v, g);
        
        // call helper recursively if not matching
        if(neighbourIterator != neighbourEnd)
        {
            return cycleHelper(g, *neighbourIterator);
        }
    }
    
    return false;
}

// returns true if the graph g contains a cycle
bool isCyclic(Graph &g)
{
    // clear visited
    clearVisited(g);
    
    // set up iterators
    Graph::vertex_iterator vertexIterator, vertexEnd;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vertices
    while (vertexIterator != vertexEnd)
    {
        // if not visited
        if (!g[*vertexIterator].visited)
        {
            // call helper and return true if true
            if (cycleHelper(g, *vertexIterator))
            {
                return true;
            }
        }
        
        // increment
        ++vertexIterator;
    }
    
    // return false if no cycles found
    return false;
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

// helper function for finding a spaning forest
void spanningHelper(Graph &g, Graph &sf, Graph::vertex_descriptor v)
{
    // set up iterators
    Graph::adjacency_iterator neighbourIterator, neighbourEnd;
    tie(neighbourIterator, neighbourEnd) = adjacent_vertices(v, g);
    
    // iterate through neighbour vertices
    while (neighbourIterator != neighbourEnd)
    {
        Graph::vertex_descriptor added;
        EdgeProperties e;
        
        // if not visited
        if (!g[*neighbourIterator].visited)
        {
            // add to forest and set visited
            added = add_vertex(sf);
            g[*neighbourIterator].visited = true;
            e.weight = g[findEdge(g, v, *neighbourIterator)].weight;
            
            // add edge
            add_edge(v, added, e, sf);
            
            // recursively call helper
            spanningHelper(g, sf, added);
        }
        
        // incremenet
        ++neighbourIterator;
    }
}

// create a graph sf that contains a spanning forest on the graph g.
void findSpanningForest(Graph &g, Graph &sf)
{
    // clear visited
    clearVisited(g);
    Graph::vertex_descriptor v;

    // set up iterators
    Graph::vertex_iterator vertexIterator, vertexEnd;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vertices
    while (vertexIterator != vertexEnd)
    {
        
        // look for disconnected elements
        if (!g[*vertexIterator].visited)
        {
            // add to forest
            v = *vertexIterator;
            g[v].visited = true;
            v = add_vertex(sf);
            spanningHelper(g, sf, v);
        }
        
        // increment
        ++vertexIterator;
        
    }
}

// print the info for the forest
void printForest(Graph &g)
{
    // set up iterators
    Graph::edge_iterator edgeIterator, edgeEnd;
    tie(edgeIterator, edgeEnd) = edges(g);
    
    // initalize cost
    int cost = 0;
    
    // iterate through edges
    while (edgeIterator != edgeEnd)
    {
        // get info for target and source
        Graph::vertex_descriptor x = target(*edgeIterator, g);
        Graph::vertex_descriptor y = source(*edgeIterator, g);
        
        // print info
        cout << "\tTarget = [" << x << "]" << "\tSource = [" << y << "]";
        
        // print weight
        cout << "\tWeight:" << g[*edgeIterator].weight << endl;
        
        // add to total cost
        cost += g[*edgeIterator].weight;
        
        // increment
        ++edgeIterator;
    }
    
    // print total cost and num connected vertices
    cout << "Total cost = " << cost << endl;
    cout << "Connected components = " << num_vertices(g) << endl << endl;
}

// min spanning forest using prim
void msfPrim(Graph &g, Graph &sf)
{
    // clear visited
    clearVisited(g);
    
    // initialize vars
    heapV<Graph::edge_descriptor, Graph> v;
    Graph::edge_iterator edgeIterator, edgeEnd;
    Graph::adjacency_iterator eneighbourIt, eneighbourEnd;
    tie(edgeIterator, edgeEnd) = edges(g);
    
    // iterate through edges
    while (edgeIterator != edgeEnd)
    {
        v.minHeapInsert(*edgeIterator, g);
        
        ++edgeIterator;
    }
    
    // set up iterator
    Graph::vertex_iterator vertexIterator, vertexEnd;
    tie(vertexIterator, vertexEnd) = vertices(g);
    
    // iterate through vertices
    while (vertexIterator != vertexEnd)
    {
        Graph::vertex_descriptor vv;
        vv = *vertexIterator;
        vv = add_vertex(sf);
        
        ++vertexIterator;
    }
    
    // do while size is greater than 0
    while (v.size() > 0)
    {
        Graph::edge_descriptor e;
        e = v.extractMinHeapMinimum(g);
        
        if (!g[target(e, g)].visited)
        {
            g[target(e, g)].visited = true;
            g[source(e, g)].visited = true;
            
            add_edge(source(e,g), target(e,g), sf);
            add_edge(target(e, g), source(e, g), sf);
            sf[findEdge(sf, source(e, g), target(e, g))].weight = g[e].weight;
            sf[findEdge(sf, target(e, g), source(e, g))].weight = g[e].weight;
        }
        
    }
    
}

// print the min forest
void printMinForest(Graph &g)
{
    // set up iterators
    Graph::edge_iterator edgeIterator, edgeEnd;
    tie(edgeIterator, edgeEnd) = edges(g);
    
    // initialize cost
    int cost = 0;
    
    // iterate through edges
    while (edgeIterator != edgeEnd)
    {
        // get info for target and source
        Graph::vertex_descriptor x = target(*edgeIterator, g);
        Graph::vertex_descriptor y = source(*edgeIterator, g);
        
        // print target and source
        cout << "\tTarget = [" << x << "]" << "\tSource = [" << y << "]";
        
        // print weight
        cout << "\tWeight:" << g[*edgeIterator].weight << endl;
        
        // add to total cost
        cost += g[*edgeIterator].weight;
        
        // increment
        ++++edgeIterator;
    }
    
    // print total cost and num connected vertices
    cout << "Total Cost = " << cost << endl;
    cout << "Connected Components = " << num_vertices(g) << endl << endl;
}

// main
int main()
{
    ifstream fin;

    // get filename
    string fileName;
    cout << "Input filename: ";
    cin >> fileName;
    cout << "\n";
    
    // open file
    fin.open(fileName.c_str());
    
    // check for file open errors
    if (!fin)
    {
        cerr << "Error: can't open " << fileName << endl;
        exit(1);
    }
    
    // declare vars
    Graph g,sf, sfMin;
    Graph::vertex_descriptor start, end;
    
    initializeGraph(g, start, end, fin);
    
    // print is connect for graph
    if (isConnected(g))
    {
        cout << "Graph is connected" << endl;
    }
    else
    {
        cout << "Graph is not connected" << endl;
    }
    
    // print is cyclic for graph
    if (isCyclic(g))
    {
        cout << "Graph is cyclic" << endl;
    }
    else
    {
        cout << "Graph is not cyclic" << endl;
    }
    
    // find spanning forest
    findSpanningForest(g, sf);
    
    // print is connected for forest
    if (isConnected(sf))
    {
        cout << "\nSpanning forest is connected" << endl;
    }
    else
    {
        cout << "\nSpanning forest is not connected" << endl;
    }
    
    // print is cyclic for forest
    if (isCyclic(sf))
    {
        cout << "Spanning forest is cyclic" << endl;
    }
    else
    {
        cout << "Spanning forest is not cyclic" << endl;
    }
    
    // print the forest info
    printForest(sf);
    
    msfPrim(g, sfMin);
    
    if (isConnected(sfMin))
    {
        cout << "Min spanning forest is connected" << endl;
    }
    else
    {
        cout << "Min spanning forest is not connected" << endl;
    }
    if (isCyclic(sfMin))
    {
        cout << "Min spanning forest is cyclic" << endl;
    }
    else
    {
        cout << "Min spanning forest is not cyclic" << endl;
    }
    
    printMinForest(sfMin);
    
    // close file and exit
    fin.close();
    return 0;
}
