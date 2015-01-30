#ifndef GRAPH_CANONIZATION_H
#define GRAPH_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/EdgeSet.h"
#include "../types/PermutationGroupCoset.h"

PermutationGroupCoset* graphCanonization(
    ElementSet*,
    EdgeSet*,
    PermutationGroupCoset*
);
ElementSet* graphInducedAction(ElementSet*, Permutation*);

#endif
