#ifndef UTILS_H
#define UTILS_H

#include "../types/ElementSet.h"
#include "../types/PermutationGroup.h"

ElementSet* findOrbit(int, int, PermutationGroup*);
ElementSet* findMinimalBlockSystem(int, ElementSet*, PermutationGroup*);
ElementSet* findBlockSystem(int, int, ElementSet*, PermutationGroup*);

#endif
