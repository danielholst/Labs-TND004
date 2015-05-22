// ===================================================================
// file:	~\tnd004\lab\lab5b\edge.cpp
// remark:	implementation of (explicit) edges
// created:	2009-05-05 / janpe
// updated:	2010-05-06 / janpe
// ===================================================================

#include <iostream>
#include <iomanip>
using namespace std;

#include "edge.h"

// -- RELATIONAL OPERATORS

bool Edge::operator< (const Edge &e) const
{
   return weight <  e.weight;
}

bool Edge::operator==(const Edge &e) const
{
   return weight == e.weight;
}

// -- FRIENDS

ostream & operator<< (ostream &os, const Edge &e)
{
    os << "(" << setw(2) << e.head   << ", "
              << setw(2) << e.tail   << ", "
              << setw(2) << e.weight << ") ";

    return os;
}
