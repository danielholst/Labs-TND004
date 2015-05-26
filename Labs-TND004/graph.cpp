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
    int current = 1;

    int totalWeight = 0;
    int counter = 1;
    int dist[size];
    int path[size];
    bool done[size];
    Edge edges[size];
    Heap<Edge> H;

    //init arrays
    for(int i = 1; i < size +1 ; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = 0;
    }

    //init start position
    dist[current] = 0;
    done[current] = true;

    //handle first next node
    Node* i =  array[current].getFirst();
    dist[i->vertex] = i->weight;
    edges[i->weight] = Edge(current, i->vertex, i->weight);
    H.insert(current, i->vertex, i->weight);
    i = array[current].getNext();

    while(!H.isEmpty())     //loop while the heap is not empty
    {
        while(i != nullptr)
        {
            //if node has not been visited
            if(!done[i->vertex] && dist[i->vertex] == INFINITY)
            {
                H.insert( i->weight );
                edges[i->weight] = Edge(current, i->vertex, i->weight);
                dist[i->vertex] = i->weight;
            }
            else if(!done[i->vertex] && i->weight < dist[i->vertex])
            {
                int f = i->vertex;
                H.insert(i->weight);
                edges[dist[f]] = Edge(0,0,0);
                edges[i->weight] = Edge(current, i->vertex, i->weight);
                dist[f] = i->weight;

                //bug of the year right here
                if(done[4] > 1) done[4] = 1;
            }
            else
//                cout << " node already visited " << endl;

            i = array[current].getNext();
        }

        if(!H.isEmpty())
        {
            int k = H.deleteMin();

            totalWeight += edges[k].weight;
            cout << edges[k] << endl;
            current = edges[k].tail;
            done[current] = true;
            i = array[current].getFirst();
            counter++;
            if(counter == size)
            {
                break;
            }
        }
    }
    cout << endl << "Total weight of graph = " << totalWeight << endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    Heap<Edge> H;         //min-heap by edges cost
    DSets D(size);

    Node* k = array[1].getFirst();
    cout << "size = " << size << endl;
    //build heap with all edges
    for(int i = 1; i < size +1 ; i++)
    {
        k = array[i].getFirst();
        while(k != nullptr)
        {
            Edge tempEdge = Edge(i, k->vertex, k->weight);
            cout << tempEdge << endl;
            H.insert(tempEdge);
            k = array[i].getNext();
        }
    }

    int counter = 0;
    cout << endl << "in next loop" << endl << endl;
    while(counter < size)
    {
        Edge tempEdge = H.deleteMin() =H.deleteMin();   //since there is duplicates of each path
        cout << tempEdge << endl;
        //if thisNode and nextNode is in the same tree
        if(D.find(tempEdge.head) != D.find(tempEdge.tail))
        {
            D.join(tempEdge.head, tempEdge.tail);
            counter++;
        }
    }

    D.print();

    cout << "hej" << endl;



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
