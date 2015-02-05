#ifndef UTILS_H
#define UTILS_H

#include "../types/ElementSet.h"
#include "../types/PermutationGroup.h"

ElementSet* findOrbit(int, int, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*);
ElementSet* findMinimalBlockSystem(int, ElementSet*, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*);
ElementSet* findBlockSystem(int, int, ElementSet*, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*);
PermutationGroup* findBlockSystemStabilizer(int, ElementSet*, ElementSet*, PermutationGroup*, Permutation***, int*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*);

ElementSet* findSubset(int, int);
int findSubsetIdx(int*, int, int);
int binom(int, int);

#endif
