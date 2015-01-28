#ifndef EDGE_SET_H
#define EDGE_SET_H

#include "Edge.h"

class EdgeSet {
    private:
    int n;
    Edge** edges;

    public:
    EdgeSet(int, Edge**);
    ~EdgeSet();
    int getN();
    Edge** getEdges();
    Edge*& operator[](const int);
};

#endif

