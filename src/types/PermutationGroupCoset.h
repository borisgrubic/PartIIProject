#ifndef PERMUTATION_GROUP_COSET_H
#define PERMUTATION_GROUP_COSET_H

#include "Permutation.h"
#include "PermutationGroup.h"

class PermutationGroupCoset {
    private:
    Permutation* permutation;
    PermutationGroup* permutationGroup;

    public:
    PermutationGroupCoset(Permutation*, PermutationGroup*);
    ~PermutationGroupCoset();
    Permutation* getPermutation();
    PermutationGroup* getGroup();
}

#endif
