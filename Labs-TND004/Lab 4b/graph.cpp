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
    Node* pointNode =  array[current].getFirst();
    dist[pointNode->vertex] = pointNode->weight;
    H.insert(Edge(current, pointNode->vertex, pointNode->weight));
    pointNode = array[current].getNext();

    while(!H.isEmpty())     //loop while the heap is not empty
    {
        while(pointNode != nullptr)
        {
            //if node has not been visited
            if(!done[pointNode->vertex] && dist[pointNode->vertex] == INFINITY)
            {
                H.insert(Edge(current, pointNode->vertex, pointNode->weight));
                dist[pointNode->vertex] = pointNode->weight;
            }
            else if(!done[pointNode->vertex] && pointNode->weight < dist[pointNode->vertex])
            {
                H.insert(Edge(current, pointNode->vertex, pointNode->weight));
                dist[pointNode->vertex] = pointNode->weight;
            }


            pointNode = array[current].getNext();
        }

        if(!H.isEmpty())
        {
            Edge k = H.deleteMin();
            while(done[k.tail])
            {
                if(H.isEmpty())
                    break;
                k = H.deleteMin();
            }

            totalWeight += k.weight;
            cout << k << endl;
            current = k.tail;
            done[current] = true;
            pointNode = array[current].getFirst();
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
    //build heap with all edges
    for(int i = 1; i < size +1 ; i++)
    {
        k = array[i].getFirst();
        while(k != nullptr)
        {
            Edge tempEdge = Edge(i, k->vertex, k->weight);
            H.insert(tempEdge);
            k = array[i].getNext();
        }
    }

    int totalWeight = 0;
    int counter = 0;
    while(counter < size-1)
    {
        Edge tempEdge = H.deleteMin();   //since there is duplicates of each path
        //if thisNode and nextNode is not in the same tree
        if(D.find(tempEdge.head) != D.find(tempEdge.tail))
        {
            D.join(D.find(tempEdge.head), D.find(tempEdge.tail));
            counter++;
            totalWeight += tempEdge.weight;
            cout << tempEdge << endl;
        }
    }

    cout << endl << "Total weight of graph = " << totalWeight << endl;
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
