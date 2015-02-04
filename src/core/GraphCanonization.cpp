#include "GraphCanonization.h"

#include "StringCanonization.h"

#include <iostream>
#include <assert.h>

ElementSet* graphInducedAction(
    ElementSet* str,
    Permutation* perm,
    ElementSet* startElems
) {
    int* resElems = new int[str->getN()];
    int n = startElems->getN();
    assert(str->getN() == n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int node1 = (*startElems)[i];
            int node2 = (*startElems)[j];
            int image1 = startElems->find((*perm)[node1]);
            int image2 = startElems->find((*perm)[node2]);
            resElems[image1 * n + image2] =
                (*str)[i * n + j];
        }
    }
    return new ElementSet(str->getN(), resElems);
}

ElementSet* getGraphRestrictedString(
    ElementSet* str,
    ElementSet* elem,
    ElementSet* startElems
) {
    int m = elem->getN();
    int n = startElems->getN();
    ElementSet* ret = new ElementSet(n * m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            int node = (*elem)[i];
            int pos = startElems->find(node);
            (*ret)[i * n + j] = (*str)[pos * n + j];
        }
    return ret;
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
            &graphInducedAction,
            &getGraphRestrictedString,
            nodes
        );

    delete adjacencyListStr;
    return result;
}
