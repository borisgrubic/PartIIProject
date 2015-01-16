#include "Utils.h"

#include <stack>
#include <stddef.h>

using namespace std;

ElementSet* findOrbit(int n, int element, PermutationGroup* group) {
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    stack<int> stack;
    stack.push(element);
    visited[element] = true;
    int size = 0;
    int gensSize = group->getGenSize();
    Permutation** gens = group->getGenerators();
    while (!stack.empty()) {
        int currentElement = stack.top();
        stack.pop();
        ++size;
        for (int i = 0; i < gensSize; ++i) {
            int newElement = (*gens[i])[currentElement];
            if (!visited[newElement]) {
                visited[newElement] = true;
                stack.push(newElement);
            }
        }
    }
    int* orbitElems = new int[size];
    int p = 0;
    for (int i = 0; i < n; ++i)
        if (visited[i]) {
            orbitElems[p++] = i;
        }
    ElementSet* orbit = new ElementSet(size, orbitElems);
    delete[] visited;
    return orbit;
}

ElementSet* findMinimalBlockSystem(
    int n, 
    ElementSet* elems, 
    PermutationGroup* group
) {
    int m = elems->getN();
    ElementSet* minimalBlockSystem = NULL;
    for (int i = 1; i < m; ++i) {
        ElementSet* blockSystem = 
            findBlockSystem(n, i, elems, group);
        if (blockSystem) {
            minimalBlockSystem = blockSystem;
            break;
        } else {
            delete blockSystem;
        }
    }
    if (minimalBlockSystem == NULL) {
        // group acts primitively on elems, so elems is the block system
        int* nelems = new int[m];
        for (int i = 0; i < m; ++i) {
            nelems[i] = (*elems)[i];
        }
        minimalBlockSystem = new ElementSet(m, nelems);
    } else {
        // group acts imprimitively on elems, try recursion
        int cnt = 0;
        for (int i = 0; i < m; ++i)
            if ((*minimalBlockSystem)[i] == (*elems)[i]) {
                // representative of its block
                ++cnt;
            }
        int p = 0;
        int* nelems = new int[cnt];
        for (int i = 0; i < m; ++i)
            if ((*minimalBlockSystem)[i] == (*elems)[i]) {
                nelems[p++] = (*elems)[i];
            }
        ElementSet* blocks = new ElementSet(cnt, nelems);
        ElementSet* finalBlocks = findMinimalBlockSystem(n, blocks, group);
        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((*minimalBlockSystem)[j] == (*blocks)[i]) {
                    (*minimalBlockSystem)[j] = (*finalBlocks)[i];
                }
            }
        } 
        delete blocks;
        delete finalBlocks;
    }
    return minimalBlockSystem;
}

ElementSet* findBlockSystem(
    int n, 
    int idx, 
    ElementSet* elems, 
    PermutationGroup* group
) {
    int gensSize = group->getGenSize();
    Permutation** gens = group->getGenerators();
    stack<int> S;
    int* blockId = new int[n];
    for (int i = 0; i < n; ++i) {
        blockId[i] = i;
    }
    blockId[(*elems)[idx]] = (*elems)[0];
    S.push((*elems)[idx]);
    while (!S.empty()) {
        int X = S.top();
        S.pop();
        int Y = blockId[X];
        for (int i = 0; i < gensSize; ++i) {
            int nX = (*gens[i])[X];
            int nY = (*gens[i])[Y];
            if (blockId[nX] == blockId[nY]) continue;
            else if (blockId[nX] > blockId[nY]) {
                swap(nX, nY);
            }
            S.push(blockId[nY]);
            int tmp = blockId[nY];
            for (int j = 0; j < n; ++j)
                if (blockId[j] == tmp) {
                    blockId[j] = blockId[nX];
                }
        }
    }
    return new ElementSet(n, blockId);
}
