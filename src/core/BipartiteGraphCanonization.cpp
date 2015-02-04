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
    int n = startElems->getN();
    std::vector<int> res;
    for (int i = 0; i < str->getN(); ++i) {
        ElementSet* subset = findSubset(i + 1, n);
        bool ok = true;
        for (int j = 0; j < subset->getN(); ++j)
            if (elems->find((*startElems)[(*subset)[j]]) == -1) {
                ok = false;
            }
        if (ok) {
            res.push_back((*str)[i]);
        }
        delete subset;
    }
    ElementSet* retSet = new ElementSet(res.size());
    for (int i = 0; i < (int)res.size(); ++i)
        (*retSet)[i] = res[i];
    return retSet;
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
    PermutationGroupCoset* tmpResult =
        stringCanonization(
            str,
            leftNodes,
            leftGroupCoset,
            &bipartiteGraphInducedAction,
            &bipartiteGetRestrictedStr,
            leftNodes
        );

    int nodeCnt = tmpResult->getPermutation()->getSize();
    Permutation* cosetPerm = new Permutation(nodeCnt);
    for (int i = 0; i < n; ++i) {
        (*cosetPerm)[(*leftNodes)[i]] = 
            (*tmpResult->getPermutation())[(*leftNodes)[i]];
    }
    Permutation** groupPerms = 
        new Permutation*[tmpResult->getGroup()->getGenSize() + 2];
    for (int i = 0; i < tmpResult->getGroup()->getGenSize(); ++i) {
        Permutation* curPerm = tmpResult->getGroup()->getGenerators()[i];
        Permutation* newPerm = new Permutation(nodeCnt);
        for (int j = 0; j < n; ++j) {
            (*newPerm)[(*leftNodes)[j]] = 
                (*curPerm)[(*leftNodes)[j]];
        }
        groupPerms[i] = newPerm;
    }
    int* perm1Array = new int[nodeCnt];
    Permutation* perm2 = new Permutation(nodeCnt);
    for (int i = 0; i < nodeCnt; ++i) {
        perm1Array[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        perm1Array[(*rightNodes)[i]] = (*rightNodes)[(i + 1) % m];
    }
    if (m > 1) {
        int tmp = (*perm2)[(*rightNodes)[0]];
        (*perm2)[(*rightNodes)[0]] = (*perm2)[(*rightNodes)[1]];
        (*perm2)[(*rightNodes)[1]] = tmp;
    }
    groupPerms[tmpResult->getGroup()->getGenSize()] = 
        new Permutation(nodeCnt, perm1Array);
    groupPerms[tmpResult->getGroup()->getGenSize() + 1] = perm2;

    PermutationGroupCoset* result = 
        new PermutationGroupCoset(
            cosetPerm,
            new PermutationGroup(
                tmpResult->getGroup()->getGenSize() + 2,
                groupPerms
            )
        );

    delete tmpResult;
    delete str;
    delete[] lastId;
    delete[] din;
    delete[] edgeCnt;
    return result;
}
