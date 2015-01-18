#include "ElementSet.h"

ElementSet::ElementSet(int nn, int* nelems) {
    n = nn;
    elems = nelems;
}

ElementSet::~ElementSet() {
    delete[] elems;
}

int ElementSet::getN() {
    return n;
}

int* ElementSet::getElems() {
    return elems;
}

int& ElementSet::operator[](const int idx) {
    if (idx >= 0 && idx < n) {
        return elems[idx];
    }
    throw "Index out of bounds";
}

ElementSet* ElementSet::substract(ElementSet* elemSet) {
    int nn = n - elemSet->getN();
    int* nelems = new int[nn];
    int j = 0;
    int p = 0;
    for (int i = 0; i < n; ++i) {
        if (j == elemSet->getN() || elems[i] != (*elemSet)[j]) {
            nelems[p++] = elems[i];
        } else {
            j++;
        }
    }
    return new ElementSet(nn, nelems);
}
