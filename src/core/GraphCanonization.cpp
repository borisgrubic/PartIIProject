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
    (void)startElems;
    ElementSet* ret = new ElementSet(elem->getN());
    for (int i = 0; i < elem->getN(); ++i)
        (*ret)[i] = (*str)[(*elem)[i]];
    return ret;
}

int getImage(
    int edgeId,
    Permutation* perm,
    ElementSet* startElems
) {
    int n = startElems->getN();
    int node1 = edgeId / n;
    int node2 = edgeId % n;
    int image1 = startElems->find((*perm)[(*startElems)[node1]]);
    int image2 = startElems->find((*perm)[(*startElems)[node2]]);
    return image1 * n + image2;
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

    ElementSet* elems = new ElementSet(n * n);
    PermutationGroupCoset* result = 
        stringCanonization(
            adjacencyListStr,
            elems,
            coset,
            &graphInducedAction,
            &getGraphRestrictedString,
            &getImage,
            nodes
        );

    delete elems;
    delete adjacencyListStr;
    return result;
}
