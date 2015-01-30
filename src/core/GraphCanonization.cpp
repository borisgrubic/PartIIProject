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
    EdgeSet* edges,
    PermutationGroupCoset* coset
) {
    int n = nodes->getN();
    int* adjacencyList = new int[n * n];
    for (int i = 0; i < n * n; ++i) adjacencyList[i] = 0;
    for (int j = 0; j < edges->getN(); ++j) {
        int from = nodes->find((*edges)[j]->getFrom());
        int dest = nodes->find((*edges)[j]->getDest());
        adjacencyList[from * n + dest] = 1;
    }
    ElementSet* adjacencyListStr = new ElementSet(n * n, adjacencyList);

    PermutationGroupCoset* result =
        stringCanonization(
            adjacencyListStr,
            nodes,
            coset,
            &graphInducedAction
        );

    delete adjacencyListStr;
    return result;
}
