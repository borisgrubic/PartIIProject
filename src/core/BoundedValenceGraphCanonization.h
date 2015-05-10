#ifndef BOUNDED_VALENCE_GRAPH_CANONIZATION_H
#define BOUNDED_VALENCE_GRAPH_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/EdgeSet.h"
#include "../types/PermutationGroupCoset.h"

#include <stddef.h>

PermutationGroupCoset* boundedValenceGraphCanonization(
    ElementSet*,
    EdgeSet*,
    int,
    int* colors = NULL
);

bool testIsomorphismBetweenBoundedValenceGraphs(
    ElementSet*,
    EdgeSet*,
    ElementSet*,
    EdgeSet*
);

bool testIsomorphismBetweenBoundedValenceGraphsSlow(
    ElementSet*,
    EdgeSet*,
    ElementSet*,
    EdgeSet* 
);

ElementSet* findMinimalAdjacencyMatrixConnected(
    ElementSet* nodes,
    EdgeSet* edges,
    int* colors = NULL
);

ElementSet* findMinimalAdjacencyMatrix(
    ElementSet* nodes,
    EdgeSet* edges,
    int* colors = NULL
);

#endif

