#include "PermutationGroup.h"

PermutationGroup::PermutationGroup(int ngenSize, Permutation** ngens) {
    genSize = ngenSize;
    gens = ngens;
}

PermutationGroup::~PermutationGroup() {
    for (int i = 0; i < genSize; ++i) {
        delete gens[i];
    }
    delete[] gens;
}

int PermutationGroup::getGenSize() {
    return genSize;
}

Permutation** PermutationGroup::getGenerators() {
    return gens;
}
