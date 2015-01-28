#ifndef UTILS_H
#define UTILS_H

#include "../types/ElementSet.h"
#include "../types/PermutationGroup.h"

ElementSet* findOrbit(int, int, PermutationGroup*);
ElementSet* findMinimalBlockSystem(int, ElementSet*, PermutationGroup*);
ElementSet* findBlockSystem(int, int, ElementSet*, PermutationGroup*);
PermutationGroup* findBlockSystemStabilizer(int, ElementSet*, ElementSet*, PermutationGroup*, Permutation***, int*);

ElementSet* findSubset(int, int);
int findSubsetIdx(int*, int, int);
int binom(int, int);

#endif
