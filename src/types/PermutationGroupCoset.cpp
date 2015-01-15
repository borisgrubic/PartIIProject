#include "PermutationGroupCoset.h"

PermutationGroupCoset::PermutationGroupCoset(
    Permutation* perm,
    PermutationGroup* permGroup
) {
    permutation = perm;
    permutationGroup = permGroup;
}

PermutationGroupCoset::~PermutationGroupCoset() {
    delete permutation;
    delete permutationGroup;
}

Permutation* PermutationGroupCoset::getPermutation() {
    return permutation;
}

PermutationGroup* PermutationGroupCoset::getGroup() {
    return permutationGroup;
}
