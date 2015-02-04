#include "Utils.h"

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
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
            if ((*minimalBlockSystem)[(*elems)[i]] == (*elems)[i]) {
                // representative of its block
                ++cnt;
            }
        int p = 0;
        int* nelems = new int[cnt];
        for (int i = 0; i < m; ++i)
            if ((*minimalBlockSystem)[(*elems)[i]] == (*elems)[i]) {
                nelems[p++] = (*elems)[i];
            }
        ElementSet* blocks = new ElementSet(cnt, nelems);
        ElementSet* finalBlocks = findMinimalBlockSystem(n, blocks, group);
        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((*minimalBlockSystem)[(*elems)[j]] == (*blocks)[i]) {
                    (*minimalBlockSystem)[(*elems)[j]] = (*finalBlocks)[i];
                }
            }
        } 
        int* resArray = new int[m];
        for (int i = 0; i < m; ++i)
            resArray[i] = (*minimalBlockSystem)[(*elems)[i]];
        delete minimalBlockSystem;
        minimalBlockSystem = new ElementSet(m, resArray);
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
    bool isTrivial = true;
    for (int i = 1; i < elems->getN(); ++i) {
        if (blockId[(*elems)[0]] != blockId[(*elems)[i]]) {
            isTrivial = false;
        }
    }
    if (isTrivial) {
        delete[] blockId;
        return NULL;
    }
    return new ElementSet(n, blockId);
}

Permutation* filter(
    vector< vector<Permutation*> >& cosetRep,
    ElementSet* elems,
    ElementSet* blockSystem,
    Permutation* filterPerm
) {
    Permutation* perm = new Permutation(filterPerm);
    for (int i = 0; i < (int)cosetRep.size(); ++i) {
        bool inCoset = false;
        for (int j = 0; j < (int)cosetRep[i].size(); ++j) {
            Permutation* tmp = cosetRep[i][j]->getInverse();
            Permutation* checkPerm = tmp->compose(perm);
            delete tmp;
            bool found = true;
            if (i == 0) {
                int m = elems->getN();
                for (int k = 0; k < m; ++k) {
                    int x = (*checkPerm)[(*elems)[k]];
                    int idx = elems->find(x);
                    if (idx == -1 || (*blockSystem)[idx] != (*blockSystem)[k]) {
                        found = false;
                        break;
                    }
                }
            } else {
                if ((*checkPerm)[i - 1] != i - 1) {
                    found = false;
                }
            }
            if (found) {
                delete perm;
                inCoset = true;
                perm = checkPerm;
                break;
            } else {
                delete checkPerm;
            }
        }
        if (!inCoset) {
            cosetRep[i].push_back(perm);
            return new Permutation(perm);
        }
    }    
    delete perm;
    return NULL;
}

PermutationGroup* findBlockSystemStabilizer(
    int n,
    ElementSet* elems, 
    ElementSet* blockSystem, 
    PermutationGroup* group, 
    Permutation*** cosetRepresentatives, 
    int* size
) {
    vector< vector<Permutation*> > cosetRep(n, vector<Permutation*>());
    vector<Permutation*> permList;
    permList.push_back(new Permutation(n));
    for (int i = 0; i < n; ++i) {
        cosetRep[i].push_back(new Permutation(n));
    }
    int gensSize = group->getGenSize();
    Permutation** generators = group->getGenerators();
    queue<Permutation*> queue;
    for (int i = 0; i < gensSize; ++i) {
        Permutation* newCoset = 
            filter(cosetRep, elems, blockSystem, generators[i]);
        if (newCoset) {
            queue.push(newCoset);
            permList.push_back(newCoset);
        }
    }
    vector<Permutation*> newPermList;
    while (!queue.empty()) {
        Permutation* curCoset = queue.front();
        queue.pop();
        newPermList.clear();
        for (int i = 0; i < (int)permList.size(); ++i) {
            Permutation* filterPerm = 
                permList[i]->compose(curCoset);
            Permutation* newCoset =
                filter(cosetRep, elems, blockSystem, filterPerm);
            if (newCoset) {
                queue.push(newCoset);
                newPermList.push_back(newCoset);
            }
            delete filterPerm;
            filterPerm = 
                curCoset->compose(permList[i]);
            newCoset =
                filter(cosetRep, elems, blockSystem, filterPerm);
            if (newCoset) {
                queue.push(newCoset);
                newPermList.push_back(newCoset);
            }
            delete filterPerm;
        }
        for (int i = 0; i < (int)newPermList.size(); ++i)
            permList.push_back(newPermList[i]);
    } 
    int stabGenSize = 1;
    for (int i = 1; i < n; ++i) {
        stabGenSize += cosetRep[i].size() - 1;
    }
    int p = 0;
    Permutation** stabGen = new Permutation*[stabGenSize]; 
    stabGen[p++] = new Permutation(n);
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < (int)cosetRep[i].size(); ++j) {
            stabGen[p++] = new Permutation(cosetRep[i][j]);
        }
    *size = cosetRep[0].size();
    *cosetRepresentatives = new Permutation*[*size];
    for (int i = 0; i < *size; ++i) {
        (*cosetRepresentatives)[i] = new Permutation(cosetRep[0][i]);
    }
    for (int i = 0; i < (int)cosetRep.size(); ++i)
        for (int j = 0; j < (int)cosetRep[i].size(); ++j)
            delete cosetRep[i][j];
    for (int i = 0; i < (int)permList.size(); ++i)
        delete permList[i];
    return new PermutationGroup(stabGenSize, stabGen);
}

int binom(int a, int b) {
    int res = 1;
    for (int i = 0; i < b; ++i) {
        res *= (a - i);
        res /= (i + 1);
    }
    return res;
}

ElementSet* findSubset(int idx, int n) {
    int cnt = 0;
    int size = 0;
    while (cnt < idx) {
        size++;
        cnt += binom(n, size);
    }
    cnt -= binom(n, size);
    int* elems = new int[size];
    int last = -1;
    for (int i = 0; i < size; ++i) {
        int cur = last + 1;
        bool stop = false;
        while (!stop) {
            int tmp = binom(n - cur - 1, size - i - 1);
            if (cnt + tmp >= idx) {
                stop = true;
            } else {
                ++cur;
                cnt += tmp;
            }
        }
        elems[i] = cur;
        last = cur;
    }
    return new ElementSet(size, elems);
}

int findSubsetIdx(int* array, int size, int n) {
    int ret = 0;
    for (int t = 1; t < size; ++t) {
        ret += binom(n, t);
    }
    int last = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = last + 1; j < array[i]; ++j) {
            ret += binom(n - j - 1, size - i - 1);
        }
        last = array[i];
    }
    return ret;
}
