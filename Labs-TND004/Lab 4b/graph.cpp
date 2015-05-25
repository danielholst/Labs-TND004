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
    int endVertex;
    int totalWeight = 0;
    int dist[size];
    int path[size];
    bool done[size];
    Edge edges[size];
    Heap<int> H;

    for(int i = 1; i < size +1 ; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = 0;
    }

    //init start position
    dist[start] = 0;
    done[start] = 1;

    Node* i =  array[start].getFirst();
    dist[i->vertex] = i->weight;
    edges[i->weight] = Edge(start, i->vertex, i->weight);
    //cout << "connected node that has not yet been visited " << i->vertex << endl;
    H.insert(i->weight);
    int counter = 1;
    int current = start;
    i = array[start].getNext();
    while(!H.isEmpty())
    {
        while(i != nullptr)
        {
//            cout << "boolean (1) " << done[4] << endl;
//            cout << "this vertex = " << i->vertex << endl;
            //if node has not been visited
            if(!done[i->vertex] && dist[i->vertex] == INFINITY)
            {
                H.insert( i->weight );
                edges[i->weight] = Edge(current, i->vertex, i->weight);
                //cout << edges[i->weight] << endl;
                dist[i->vertex] = i->weight;
                //cout << "connected node that has not yet been visited "<< i->vertex << endl;
            }
            else if((done[i->vertex] != 1) && (i->weight < dist[i->vertex]))
            {
                int f = i->vertex;
//                cout << "boolean (3)" << done[4] << endl;
                //cout << " replace value .." << edges[dist[f]].weight << " with " << i->weight << endl;
                H.insert(i->weight);
//                cout << "boolean (4)" << done[4] << endl;
                edges[dist[f]] = Edge(0,0,0);
//                cout << "boolean (5)" << done[4] << endl;
                edges[i->weight] = Edge(current, i->vertex, i->weight);
                //cout << edges[i->weight] << endl;
//                cout << "boolean (6)" << done[4] << endl;
                dist[f] = i->weight;
                if(done[4] > 1) done[4] = 1;
//                cout << "boolean (7)" << done[4] << endl;

            }
            else
                //cout << "already visited this node .. " << endl;

            i = array[current].getNext();
        }

        if(!H.isEmpty())
        {
            int k = H.deleteMin();

//            while(edges[k].head == 0)
//            {
//                cout << "throw " << k << "and get next from heap .." << endl;
//                if(H.isEmpty())
//                    return;
//                k = H.deleteMin();
//            }
            totalWeight += edges[k].weight;
            cout << edges[k] << endl;
            current = edges[k].tail;
            //cout << "move to -> " << current << endl;
            done[current] = 1;
            //cout << edges[current] << endl;
            i = array[current].getFirst();
            counter++;
            if(counter == size)
            {
                endVertex = current;
                //cout << "endVertex = " << endVertex << endl;
                break;
            }


        }

    }
    cout << endl << "Total weight of graph = " << totalWeight << endl;

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
