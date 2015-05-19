// ===================================================================
// file:	~\tnd004\lab\lab5b\edge.h
// remark:	interface for (explicit) edges
// created:	2009-05-05 / janpe
// updated:	2010-05-06 / janpe
// ===================================================================

#ifndef EDGE_H
#define EDGE_H

#include <utility>
using namespace std::rel_ops;

class Edge {
public:
    // -- CONSTRUCTORS
    Edge(int u = 0, int v = 0, int w = 0)
    : head(u), tail(v), weight(w) { }
    // -- RELATIONAL OPERATORS
    bool operator< (const Edge &e) const;
    bool operator==(const Edge &e) const;
    // -- FRIENDS
    friend ostream & operator<< (ostream &os, const Edge &e);
    // -- DATA MEMBERS
    int head;
    int tail;
    int weight;
};

#endif
