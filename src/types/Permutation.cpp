#include "Permutation.h"

Permutation::Permutation(int n) {
    size = n;
    perm = new int[size];
    for (int i = 0; i < size; ++i) {
        perm[i] = i;
    }
}

Permutation::Permutation(Permutation* nperm) {
    size = nperm->getSize();
    perm = new int[size];
    for (int i = 0; i < size; ++i) {
        perm[i] = (*nperm)[i];
    }
}

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
    if (idx >= 0 && idx < size) {
        return perm[idx];
    }
    throw "Index out of bounds";
}

Permutation* Permutation::getInverse() {
    int* nperm = new int[size];
    for (int i = 0; i < size; ++i) {
        nperm[perm[i]] = i;
    }
    return new Permutation(size, nperm);
}

Permutation* Permutation::compose(Permutation* perm) {
    int* nperm = new int[size];
    for (int i = 0; i < size; ++i) {
        nperm[i] = (*perm)[(*this)[i]];
    }
    return new Permutation(size, nperm);
}
