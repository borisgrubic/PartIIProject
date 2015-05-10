#include "BipartiteGraphCanonization.h"

#include "StringCanonization.h"
#include "../utils/Utils.h"
#include "../types/Permutation.h"

#include <algorithm>
#include <vector>

ElementSet* bipartiteGetRestrictedStr(
    ElementSet* str,
    ElementSet* elems,
    ElementSet* startElems
) {
    (void)startElems;
    ElementSet* ret = new ElementSet(elems->getN());
    for (int i = 0; i < elems->getN(); ++i)
        (*ret)[i] = (*str)[(*elems)[i]];
    return ret;
    // int n = startElems->getN();
    // std::vector<int> res;
    // for (int i = 0; i < str->getN(); ++i) {
    //     ElementSet* subset = findSubset(i + 1, n);
    //     bool ok = true;
    //     for (int j = 0; j < subset->getN(); ++j)
    //         if (elems->find((*startElems)[(*subset)[j]]) == -1) {
    //             ok = false;
    //         }
    //     if (ok) {
    //         res.push_back((*str)[i]);
    //     }
    //     delete subset;
    // }
    // ElementSet* retSet = new ElementSet(res.size());
    // for (int i = 0; i < (int)res.size(); ++i)
    //     (*retSet)[i] = res[i];
    // return retSet;
}

ElementSet* bipartiteGraphInducedAction(
    ElementSet* str, 
    Permutation* perm,
    ElementSet* startElems
) {
    int n = startElems->getN();
    int* resElems = new int[str->getN()];
    int* nsubset = new int[n];
    for (int i = 0; i < str->getN(); ++i) {
        ElementSet* subset = findSubset(i + 1, n);
        for (int j = 0; j < subset->getN(); ++j) {
            nsubset[j] = startElems->find((*perm)[(*startElems)[(*subset)[j]]]);
        }
        std::sort(nsubset, nsubset + subset->getN());
        int nsubsetIdx = 
            findSubsetIdx(nsubset, subset->getN(), n);
        resElems[nsubsetIdx] = (*str)[i];
        delete subset;
    }
    delete[] nsubset;
    return new ElementSet(str->getN(), resElems);
}

int bipartiteGetImage(
    int element,
    Permutation* perm,
    ElementSet* startElems
) {
    int n = startElems->getN();
    ElementSet* subset = findSubset(element + 1, n);
    int* nsubset = new int[subset->getN()];
    for (int j = 0; j < subset->getN(); ++j) {
        nsubset[j] = startElems->find((*perm)[(*startElems)[(*subset)[j]]]);
    }

    std::sort(nsubset, nsubset + subset->getN());
    int ret = findSubsetIdx(nsubset, subset->getN(), n);
    delete subset;
    delete[] nsubset;
    return ret;
}

PermutationGroupCoset* bipartiteGraphCanonization(
    ElementSet* leftNodes,
    ElementSet* rightNodes,
    EdgeSet* edgeSet,
    PermutationGroupCoset* leftGroupCoset
) {
    int m = rightNodes->getN();
    if (m == 0) {
        return new PermutationGroupCoset(leftGroupCoset);
    }
    int* din = new int[m];
    for (int i = 0; i < m; ++i)
        din[i] = 0;
    for (int i = 0; i < edgeSet->getN(); ++i) {
        int rightNode = (*edgeSet)[i]->getDest();
        int idx = rightNodes->find(rightNode);
        if (idx == -1) {
            idx = rightNodes->find((*edgeSet)[i]->getFrom());
        }
        din[idx]++;
    }
    int maxDin = din[0];
    for (int i = 1; i < m; ++i) {
        if (maxDin < din[i]) {
            maxDin = din[i];
        }
    }
    int n = leftNodes->getN();
    int cnt = 0;
    int cur = 1;
    for (int i = 1; i <= maxDin; ++i) {
        cur *= (n - i + 1);
        cur /= i;
        cnt += cur;
    }

    int* elems = new int[cnt];
    int* edgeCnt = new int[m];
    int* lastId = new int[m];
    for (int i = 0; i < cnt; ++i) {
        ElementSet* subset = findSubset(i + 1, n);

        for (int j = 0; j < m; ++j) {
            lastId[j] = -1;
            edgeCnt[j] = 0;
        }
        for (int j = 0; j < edgeSet->getN(); ++j) {
            Edge* edge = (*edgeSet)[j];
            int from = edge->getFrom();
            int dest = edge->getDest();
            if (leftNodes->find(from) == -1) {
                std::swap(from, dest);
            }
            int fromIdx = leftNodes->find(from);
            int destIdx = rightNodes->find(dest);
            if (subset->find(fromIdx) != -1 && lastId[destIdx] != fromIdx) {
                ++edgeCnt[destIdx];
                lastId[destIdx] = fromIdx;
            }
        }

        elems[i] = 0;
        for (int j = 0; j < m; ++j)
            if (edgeCnt[j] == subset->getN()) {
                ++elems[i];
            }

        delete subset;
    }

    ElementSet* str = new ElementSet(cnt, elems);
    ElementSet* elemsSet = new ElementSet(cnt);
    PermutationGroupCoset* tmpResult =
        stringCanonization(
            str,
            elemsSet,
            leftGroupCoset,
            &bipartiteGraphInducedAction,
            &bipartiteGetRestrictedStr,
            &bipartiteGetImage,
            leftNodes
        );

    std::vector<int> idx;
    std::vector<int> adjVec[m];
    Permutation* perm = tmpResult->getPermutation();
    for (int i = 0; i < m; ++i) idx.push_back(i);
    for (int i = 0; i < edgeSet->getN(); ++i) {
        Edge* edge = (*edgeSet)[i];
        int from = edge->getFrom();
        int dest = edge->getDest();
        if (leftNodes->find(from) == -1) {
            std::swap(from, dest);
        }
        int destIdx = rightNodes->find(dest);
        adjVec[destIdx].push_back((*perm)[from]);
    }
    for (int i = 0; i < m; ++i)
        std::sort(adjVec[i].begin(), adjVec[i].end());
    for (int ii = 0; ii < m; ++ii)
        for (int jj = ii + 1; jj < m; ++jj) {
            int i = idx[ii];
            int j = idx[jj];
            int t = std::min(adjVec[i].size(), adjVec[j].size());
            int smaller = -1;
            for (int k = 0; k < t && smaller == -1; ++k)
                if (adjVec[j][k] != adjVec[i][k])
                    smaller = (adjVec[j][k] > adjVec[i][k]);
            if (smaller == -1) smaller = (adjVec[j].size() < adjVec[i].size());
            if (smaller == 1) {
                std::swap(idx[ii], idx[jj]);
            }
        }

    int additional = 0;
    int curCnt = 1;
    for (int i = 1; i < m; ++i) {
        if (adjVec[idx[i]] == adjVec[idx[i - 1]]) {
            ++curCnt;
        } else {
            if (curCnt >= 2) {
                ++additional;
            }
            if (curCnt > 2) {
                ++additional;
            }
            curCnt = 1;
        }
    }
    if (curCnt >= 2) ++additional;
    if (curCnt > 2) ++additional;

    int nodeCnt = tmpResult->getPermutation()->getSize();
    Permutation* cosetPerm = new Permutation(nodeCnt);
    for (int i = 0; i < n; ++i) {
        (*cosetPerm)[(*leftNodes)[i]] = 
            (*tmpResult->getPermutation())[(*leftNodes)[i]];
    }
    for (int i = 0; i < m; ++i) {
        (*cosetPerm)[(*rightNodes)[idx[i]]] =
            (*rightNodes)[i];
    }
    Permutation** groupPerms = 
        new Permutation*[tmpResult->getGroup()->getGenSize() + additional];
    for (int i = 0; i < tmpResult->getGroup()->getGenSize(); ++i) {
        Permutation* curPerm = tmpResult->getGroup()->getGenerators()[i];
        Permutation* newPerm = new Permutation(nodeCnt);
        for (int j = 0; j < n; ++j) {
            (*newPerm)[(*leftNodes)[j]] = 
                (*curPerm)[(*leftNodes)[j]];
        }
        groupPerms[i] = newPerm;
    }

    curCnt = 1;
    int nxt = tmpResult->getGroup()->getGenSize();
    for (int i = 1; i < m + 1; ++i) {
        if (i < m && adjVec[idx[i]] == adjVec[idx[i - 1]]) {
            ++curCnt;
        } else {
            if (curCnt > 1) {
                Permutation* perm1 = new Permutation(nodeCnt);
                for (int j = i - curCnt; j < i; ++j) {
                    int k = j + 1;
                    if (j == i - 1) k = i - curCnt;
                    (*perm1)[(*rightNodes)[j]] = (*rightNodes)[k];
                }
                groupPerms[nxt++] = perm1;

                if (curCnt > 2) {
                    Permutation* perm2 = new Permutation(nodeCnt);
                    (*perm2)[(*rightNodes)[i - 1]] = (*rightNodes)[i - 2];
                    (*perm2)[(*rightNodes)[i - 2]] = (*rightNodes)[i - 1];
                    groupPerms[nxt++] = perm2;
                }
            }

            curCnt = 1;
        }
    }

    // int* perm1Array = new int[nodeCnt];
    // Permutation* perm2 = new Permutation(nodeCnt);
    // for (int i = 0; i < nodeCnt; ++i) {
    //     perm1Array[i] = i;
    // }
    // for (int i = 0; i < m; ++i) {
    //     perm1Array[(*rightNodes)[i]] = (*rightNodes)[(i + 1) % m];
    // }
    // if (m > 1) {
    //     int tmp = (*perm2)[(*rightNodes)[0]];
    //     (*perm2)[(*rightNodes)[0]] = (*perm2)[(*rightNodes)[1]];
    //     (*perm2)[(*rightNodes)[1]] = tmp;
    // }
    // groupPerms[tmpResult->getGroup()->getGenSize()] = 
    //     new Permutation(nodeCnt, perm1Array);
    // groupPerms[tmpResult->getGroup()->getGenSize() + 1] = perm2;

    PermutationGroupCoset* result = 
        new PermutationGroupCoset(
            cosetPerm,
            new PermutationGroup(
                tmpResult->getGroup()->getGenSize() + additional,
                groupPerms
            )
        );

    delete elemsSet;
    delete tmpResult;
    delete str;
    delete[] lastId;
    delete[] din;
    delete[] edgeCnt;
    return result;
}
