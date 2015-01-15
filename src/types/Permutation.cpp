#include "Permutation.h"

Permutation::Permutation(int nsize, int* nperm) {
    size = nsize;
    perm = nperm;
}

Permutation::~Permutation() {
    delete[] perm;
}

int Permutation::getSize() {
    return size;
}

int* Permutation::getPermutation() {
    return perm;
}

int& Permutation::operator[](const int idx) {
    if (idx >= 1 && idx <= size) {
        return perm[idx];
    }
    return -1;
}

Permutation* Permutation::getInverse() {
    int* nperm = new int[size];
    for (int i = 0; i < size; ++i) {
        nperm[perm[i]] = i;
    }
    return new Permutation(size, nperm);
}
