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
    PermutationGroupCoset(PermutationGroupCoset*);
    ~PermutationGroupCoset();
    Permutation* getPermutation();
    PermutationGroup* getGroup();
    void setPermutation(Permutation*);
};

#endif
