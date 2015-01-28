#ifndef BIPARTITE_GRAPH_CANONIZATION_H
#define BIPARTITE_GRAPH_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/EdgeSet.h"
#include "../types/PermutationGroupCoset.h"

PermutationGroupCoset* bipartiteGraphCanonization(
    ElementSet* leftNodes,
    ElementSet* rightNodes,
    EdgeSet* edgeSet,
    PermutationGroupCoset* leftGroupCoset
);

#endif

