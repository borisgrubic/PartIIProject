#include "ElementSet.h"

ElementSet::ElementSet(ElementSet* elemSet) {
    n = elemSet->getN();
    elems = new int[n];
    for (int i = 0; i < n; ++i)
        elems[i] = (*elemSet)[i];
}

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

bool ElementSet::operator==(ElementSet& other) {
    if (n != other.getN()) return false;
    for (int i = 0; i < n; ++i)
        if ((*this)[i] != other[i])
            return false;
    return true;
}

bool ElementSet::operator<(ElementSet& other) {
    int limit = n;
    if (other.n < limit) {
        limit = other.n;
    }
    for (int i = 0; i < limit; ++i)
        if ((*this)[i] != other[i])
            return (*this)[i] < other[i];
    return n < other.n;
}

int ElementSet::find(int x) {
    for (int i = 0; i < n; ++i)
        if (elems[i] == x)
            return i;
    return -1;
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
