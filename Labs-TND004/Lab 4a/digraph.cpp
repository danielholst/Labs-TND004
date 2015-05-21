// ===================================================================
// file:	~\tnd004\lab\lab5a\digraph.cpp
// remark:	implementation of directed graphs
// created:	2009-05-03 / janpe
// updated:	2010-05-05 / janpe
// ===================================================================

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
        cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
        return;
    }

    //case if first node is not connected to any nodes
    else if(array[s].getFirst() == nullptr)
    {
        dist[s] = 0;
        done[s] = true;
        cout << " No connected nodes " << endl;
    }

    else
    {
        Queue<int> Q;

        //initialize the distance and paths
        for(int i = 0; i < size+1; i++)
        {
            dist[i] = INFINITY;
            path[i] = 0;
        }

        //set distance of start position to 0
        dist[s] = 0;
        done[s] = true;
        Q.enqueue(s);

        while(!Q.isEmpty())
        {
            //cout << "debug: In first while " << endl;
            int thisVal = Q.getFront();
            Q.dequeue();

            Node* p = array[thisVal].getFirst();

            //cout << "debug: first value = " << p->vertex << endl;
            while(p != nullptr)
            {
                //cout << "debug: In second while" << endl;
                int nextVal = p->vertex;
                if(p != nullptr)
                {
                    if(dist[nextVal] == INFINITY)    //if next node haven't been visited
                    {
                        cout << "debug: next has not been visited " << endl;
                        dist[nextVal] = dist[thisVal] + 1;
                        path[nextVal] = thisVal;
                        Q.enqueue(nextVal);
                        cout << "added " << nextVal << " to the queue " << endl;
                    }
                    else
                        cout << "debug: next node has already been visited ( " << nextVal << " )" << endl;
                }
                p = array[thisVal].getNext();
            }
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
        cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
        return;
    }

    // *** TODO ***
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
        cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
        return;
    }

    // *** TODO ***
}
