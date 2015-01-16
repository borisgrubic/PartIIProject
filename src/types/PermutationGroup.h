#ifndef PERMUTATION_GROUP_H
#define PERMUTATION_GROUP_H

#include "Permutation.h"

class PermutationGroup {
    private:
    int genSize;
    Permutation** gens;

    public:
    PermutationGroup(int, Permutation**);
    ~PermutationGroup();
    int getGenSize();
    Permutation** getGenerators();
};

#endif
