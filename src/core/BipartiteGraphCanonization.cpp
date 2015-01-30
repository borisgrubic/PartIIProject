#include "BipartiteGraphCanonization.h"

#include "StringCanonization.h"
#include "../utils/Utils.h"
#include "../types/Permutation.h"

#include <algorithm>

ElementSet* bipartiteGraphInducedAction(ElementSet* str, Permutation* perm) {
    int* resElems = new int[str->getN()];
    int* nsubset = new int[perm->getSize()];
    for (int i = 0; i < str->getN(); ++i) {
        ElementSet* subset = findSubset(i + 1, perm->getSize());
        for (int j = 0; j < subset->getN(); ++j) {
            nsubset[j] = (*perm)[(*subset)[j]];
        }
        std::sort(nsubset, nsubset + subset->getN());
        int nsubsetIdx = 
            findSubsetIdx(nsubset, subset->getN(), perm->getSize());
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
    int* din = new int[m];
    for (int i = 0; i < m; ++i)
        din[i] = 0;
    for (int i = 0; i < edgeSet->getN(); ++i) {
        int rightNode = (*edgeSet)[i]->getDest();
        int idx = rightNodes->find(rightNode);
        if (idx == -1) {
            idx = rightNodes->find((*edgeSet)[i]->getFrom());
        }
        din[rightNodes->find(rightNode)]++;
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
    for (int i = 0; i < m; ++i) lastId[i] = -1;
    for (int i = 0; i < cnt; ++i) {
        ElementSet* subset = findSubset(i + 1, n);

        for (int j = 0; j < m; ++j) {
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
    ElementSet* elemSet = new ElementSet(cnt);
    PermutationGroupCoset* tmpResult =
        stringCanonization(
            str,
            elemSet,
            leftGroupCoset,
            &bipartiteGraphInducedAction
        );

    Permutation* cosetPerm = new Permutation(n + m);
    for (int i = 0; i < n; ++i) {
        (*cosetPerm)[(*leftNodes)[i]] = 
            (*leftNodes)[(*tmpResult->getPermutation())[i]];
    }
    for (int i = 0; i < m; ++i) {
        (*cosetPerm)[(*rightNodes)[i]] = (*rightNodes)[i];
    }
    Permutation** groupPerms = 
        new Permutation*[tmpResult->getGroup()->getGenSize() + 2];
    for (int i = 0; i < tmpResult->getGroup()->getGenSize(); ++i) {
        Permutation* curPerm = tmpResult->getGroup()->getGenerators()[i];
        Permutation* newPerm = new Permutation(n + m);
        for (int j = 0; j < n; ++j) {
            (*newPerm)[(*leftNodes)[j]] = (*leftNodes)[(*curPerm)[j]];
        }
        for (int j = 0; j < m; ++j) {
            (*newPerm)[(*rightNodes)[j]] = (*rightNodes)[j];
        }
        groupPerms[i] = newPerm;
    }
    int* perm1Array = new int[n + m];
    Permutation* perm2 = new Permutation(n + m);
    for (int i = 0; i < n; ++i) {
        perm1Array[(*leftNodes)[i]] = (*leftNodes)[i];
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
        new Permutation(n + m, perm1Array);
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
    delete elemSet;
    delete[] lastId;
    delete[] din;
    delete[] edgeCnt;
    return result;
}
