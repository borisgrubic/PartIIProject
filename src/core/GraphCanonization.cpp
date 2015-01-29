#include "GraphCanonization.h"

#include "StringCanonization.h"

#include <iostream>
#include <assert.h>

ElementSet* graphInducedAction(ElementSet* str, Permutation* perm) {
    int* resElems = new int[str->getN()];
    int n = perm->getSize();
    assert(str->getN() == n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resElems[(*perm)[i] * n + (*perm)[j]] =
                (*str)[i * n + j];
        }
    }
    return new ElementSet(str->getN(), resElems);
}

PermutationGroupCoset* graphCanonization(
    ElementSet* nodes, 
    EdgeSet* edges
) {
    int n = nodes->getN();
    int* adjacencyList = new int[n * n];
    for (int i = 0; i < n * n; ++i) adjacencyList[i] = 0;
    for (int j = 0; j < edges->getN(); ++j) {
        int from = (*edges)[j]->getFrom();
        int dest = (*edges)[j]->getDest();
        adjacencyList[from * n + dest] = 1;
    }
    ElementSet* adjacencyListStr = new ElementSet(n * n, adjacencyList);

    int* permArray1 = new int[n];
    int* permArray2 = new int[n];
    for (int i = 0; i < n; ++i) {
        permArray1[i] = (i + 1) % n;
        permArray2[i] = i;
    }
    if (n > 1) {
        std::swap(permArray2[0], permArray2[1]);
    }
    PermutationGroupCoset* coset =
        new PermutationGroupCoset(
            new Permutation(n),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(n, permArray1),
                    new Permutation(n, permArray2)
                }
            )
        );

    PermutationGroupCoset* result =
        stringCanonization(
            adjacencyListStr,
            nodes,
            coset,
            &graphInducedAction
        );

    delete adjacencyListStr;
    delete coset;
    return result;
}
