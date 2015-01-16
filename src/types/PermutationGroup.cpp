#include "PermutationGroup.h"

PermutationGroup::PermutationGroup(PermutationGroup* group) {
    genSize = group->getGenSize();
    Permutation** gensCopy = group->getGenerators();
    gens = new Permutation*[genSize];
    for (int i = 0; i < genSize; ++i) {
        gens[i] = new Permutation(gensCopy[i]);
    }
}

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
