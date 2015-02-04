#ifndef STRING_CANONIZATION_H
#define STRING_CANONIZATION_H

#include "../types/ElementSet.h"
#include "../types/Permutation.h"
#include "../types/PermutationGroupCoset.h"

PermutationGroupCoset* stringCanonization(
    ElementSet* str,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*),
    ElementSet* (*getRestrictedString)(ElementSet*, ElementSet*, ElementSet*),
    ElementSet*
);

#endif
