#ifndef STRING_CANONIZATION_H
#define STRING_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/Permutation.h"
#include "../types/PermutationGroupCoset.h"

PermutationGroupCoset stringCanonization(
    string str,
    ElementSet elems,
    PermutationGroupCoset coset,
    string (*inducedAction)(string, Permutation)
);

#endif
