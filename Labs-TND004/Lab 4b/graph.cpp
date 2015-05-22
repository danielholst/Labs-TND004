// ===================================================================
// file:	~\tnd004\lab\lab5b\graph.cpp
// remark:	implementation of undirected graphs
// created:	2009-05-03 / janpe
// updated:	2010-05-06 / janpe
// ===================================================================

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{

    //start vertex
    int start = 5;

    int dist[size];
    int path[size];
    bool done[size];
    Heap<int> H;

    for(int i = 0; i < size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    //init start position
    dist[start] = 0;
    done[start] = true;

    Node* i =  array[start].getFirst();
    done[i->vertex] = true;
    dist[i->vertex] = i->weight;
    Edge E = Edge(start, i->vertex, i->weight);
    cout << i->vertex << " ";
    H.insert(E.weight);

    i = array[start].getNext();
    while(!H.isEmpty())
    {

        while(i != nullptr)
        {

            //if node has not been visited
            if(!done[i->vertex])
            {
                H.insert( i->weight );
                done[i->vertex] = true;
                dist[i->vertex] = i->weight;
                //path[i->vertex] =
                cout << i->vertex << " ";
            }
            i = array[start].getNext();

        }
        int k = H.deleteMin();
        i = array[start].getFirst();
        while (i != nullptr)
        {
            //find shortest path
            if( i->weight == k)
            {
                cout << " found shortest path -> to " << i->vertex << endl;
                start = i->vertex;
                i = array[start].getFirst();
                break;
            }
            i = array[start].getNext();

        }

    }
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
