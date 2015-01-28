#include "EdgeSet.h"

EdgeSet::EdgeSet(int nn, Edge** nedges) {
    n = nn;
    edges = nedges;
}

EdgeSet::~EdgeSet() {
    for (int i = 0; i < n; ++i)
        delete edges[i];
    delete[] edges;
}

int EdgeSet::getN() {
    return n;
}

Edge** EdgeSet::getEdges() {
    return edges;
}

Edge*& EdgeSet::operator[](const int idx) {
    if (idx >= 0 && idx < n) {
        return edges[idx];
    }
    throw "Index out of bounds";
}
