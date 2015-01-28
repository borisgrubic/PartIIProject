#include "TestBipartiteGraphCanonization.h"

#include "../../src/core/BipartiteGraphCanonization.h"
#include "../../src/utils/Utils.h"
#include "TestStringCanonization.h"

bool TestBipartiteGraphCanonization::testBipartiteGraphCanonization(
    ElementSet* leftNodes1,
    ElementSet* rightNodes1,
    EdgeSet* edgeSet1,
    ElementSet* leftNodes2,
    ElementSet* rightNodes2,
    EdgeSet* edgeSet2,
    PermutationGroupCoset* leftGroupCoset,
    bool resultsAreSame
) {
    PermutationGroupCoset* result1 =
        bipartiteGraphCanonization(
            leftNodes1, 
            rightNodes1, 
            edgeSet1, 
            leftGroupCoset
        );
    PermutationGroupCoset* result2 =
        bipartiteGraphCanonization(
            leftNodes2, 
            rightNodes2, 
            edgeSet2, 
            leftGroupCoset
        );

    bool ret = true;

    int n = leftNodes1->getN();
    int m = rightNodes1->getN();
    int cnt = (1 << n) - 1;
    bool same = true;
    int* edgeCnt1 = new int[m];
    int* edgeCnt2 = new int[m];
    for (int i = 0; i < cnt; ++i) {
        ElementSet* subset = findSubset(i + 1, n);

        for (int j = 0; j < m; ++j) {
            edgeCnt1[j] = 0;
            edgeCnt2[j] = 0;
        }
        for (int j = 0; j < edgeSet1->getN(); ++j) {
            Edge* edge = (*edgeSet1)[j];
            int from = (*result1->getPermutation())[edge->getFrom()];
            if (subset->find(leftNodes1->find(from)) != -1) {
                ++edgeCnt1[rightNodes1->find(edge->getDest())];
            }
        }
        for (int j = 0; j < edgeSet2->getN(); ++j) {
            Edge* edge = (*edgeSet2)[j];
            int from = (*result2->getPermutation())[edge->getFrom()];
            if (subset->find(leftNodes2->find(from)) != -1) {
                ++edgeCnt2[rightNodes2->find(edge->getDest())];
            }
        }

        int sum = 0;
        for (int j = 0; j < m; ++j) {
            if (edgeCnt1[j] == subset->getN()) {
                ++sum;
            }
            if (edgeCnt2[j] == subset->getN()) {
                --sum;
            }
        }
        same &= (sum == 0);

        delete subset;
    }

    ret &= (same == resultsAreSame);

    delete[] edgeCnt1;
    delete[] edgeCnt2;
    delete leftNodes1;
    delete rightNodes1;
    delete edgeSet1;
    delete leftNodes2;
    delete rightNodes2;
    delete edgeSet2;
    delete leftGroupCoset;
    delete result1;
    delete result2;
    return ret;
}


bool TestBipartiteGraphCanonization::test() {
    bool ok = true;
    ok &= testBipartiteGraphCanonization(
        new ElementSet(2, new int[2]{0, 2}),
        new ElementSet(2, new int[2]{1, 3}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(0, 1),
            new Edge(0, 3),
            new Edge(2, 1)
        }),
        new ElementSet(2, new int[2]{0, 1}),
        new ElementSet(2, new int[2]{2, 3}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(0, 2),
            new Edge(0, 3),
            new Edge(1, 3)
        }),
        new PermutationGroupCoset(
            new Permutation(2),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(2),
                    new Permutation(2, new int[2]{1, 0})
                }
            )
        ),
        true
    );
    ok &= testBipartiteGraphCanonization(
        new ElementSet(2, new int[2]{0, 2}),
        new ElementSet(2, new int[2]{1, 3}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(0, 1),
            new Edge(0, 3),
            new Edge(2, 1)
        }),
        new ElementSet(2, new int[2]{0, 1}),
        new ElementSet(2, new int[2]{2, 3}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(1, 2),
            new Edge(1, 3),
            new Edge(0, 3)
        }),
        new PermutationGroupCoset(
            new Permutation(2),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(2),
                    new Permutation(2, new int[2]{1, 0})
                }
            )
        ),
        true
    );
    ok &= testBipartiteGraphCanonization(
        new ElementSet(2, new int[2]{0, 1}),
        new ElementSet(3, new int[3]{2, 3, 4}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(0, 2),
            new Edge(0, 4),
            new Edge(1, 3)
        }),
        new ElementSet(2, new int[2]{0, 1}),
        new ElementSet(3, new int[3]{2, 3, 4}),
        new EdgeSet(3, new Edge*[3]{
            new Edge(0, 2),
            new Edge(0, 4),
            new Edge(1, 4)
        }),
        new PermutationGroupCoset(
            new Permutation(2),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(2),
                    new Permutation(2, new int[2]{1, 0})
                }
            )
        ),
        false
    );

    return ok;
}
