#ifndef GENERAL_GRAPH_CANONIZATION_H
#define GENERAL_GRAPH_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/EdgeSet.h"
#include "../types/PermutationGroupCoset.h"

ElementSet* generalGraphCanonization(
    ElementSet*,
    EdgeSet*
);

bool testIsomorphismBetweenGeneralGraphs(
    ElementSet*,
    EdgeSet*,
    ElementSet*,
    EdgeSet*
);

#endif

