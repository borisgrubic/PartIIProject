#include "TestBoundedValenceGraphCanonization.h"

#include "../../src/core/BoundedValenceGraphCanonization.h"
#include "../../src/core/GraphCanonization.h"
#include "TestGraphCanonization.h"

bool TestBoundedValenceGraphCanonization::testBoundedValenceGraphCanonization(
    ElementSet* nodes1,
    EdgeSet* edges1,
    ElementSet* nodes2,
    EdgeSet* edges2,
    bool resultsAreSame
) {
    int n = nodes1->getN();
    int m = nodes2->getN();
    int edges1Cnt = edges1->getN();
    int edges2Cnt = edges2->getN();
    ElementSet* nodes = new ElementSet(n + m + 2);
    Edge** edges = new Edge*[edges1Cnt + edges2Cnt + 4];
    for (int i = 0; i < edges1Cnt; ++i)
        edges[i] = new Edge((*edges1)[i]);
    for (int i = 0; i < edges2Cnt; ++i) {
        edges[i + edges1Cnt] = 
            new Edge(
                (*edges2)[i]->getFrom() + n,
                (*edges2)[i]->getDest() + n
            );
    }
    edges[edges1Cnt + edges2Cnt] = new Edge(n + m, edges[0]->getDest());
    edges[0]->setDest(n + m);
    edges[edges1Cnt + edges2Cnt + 1] = new Edge(n + m, n + m + 1);
    edges[edges1Cnt + edges2Cnt + 2] = new Edge(n + m + 1, n + m);
    edges[edges1Cnt + edges2Cnt + 3] = new Edge(n + m + 1, 0);
    EdgeSet* edgeSet = new EdgeSet(edges1Cnt + edges2Cnt + 4, edges);
    bool same = false;
    for (int i = 0; i < edges2Cnt; ++i) {
        edges[edges1Cnt + edges2Cnt + 3]->setDest(
            edges[edges1Cnt + i]->getDest()
        );
        edges[edges1Cnt + i]->setDest(n + m + 1);

        PermutationGroupCoset* result =
            boundedValenceGraphCanonization(
                nodes,
                edgeSet,
                edges1Cnt + edges2Cnt + 1
            );

        for (int j = 0; j < result->getGroup()->getGenSize(); ++j) {
            Permutation* perm = result->getGroup()->getGenerators()[j];
            if ((*perm)[n + m] == n + m + 1 && (*perm)[n + m + 1] == n + m) {
                same = true;
            }
        }
        delete result;

        edges[edges1Cnt + i]->setDest(
            edges[edges1Cnt + edges2Cnt + 3]->getDest()
        );
    }


    bool ret = (resultsAreSame == same);

    delete nodes1;
    delete edges1;
    delete nodes2;
    delete edges2;
    delete edgeSet;
    delete nodes;
    return ret;
}

bool TestBoundedValenceGraphCanonization::test() {
    bool ok = true;
    ok &= testBoundedValenceGraphCanonization(
        new ElementSet(3, new int[3]{0, 1, 2}),
        new EdgeSet(
            2,
            new Edge*[2]{
                new Edge(0, 1),
                new Edge(1, 2)
            }
        ),
        new ElementSet(3, new int[3]{0, 1, 2}),
        new EdgeSet(
            2,
            new Edge*[2]{
                new Edge(0, 2),
                new Edge(2, 1)
            }
        ),
        true
    );
    // ok &= testBoundedValenceGraphCanonization(
    //     new ElementSet(4, new int[4]{0, 1, 2, 3}),
    //     new EdgeSet(
    //         8,
    //         new Edge*[8]{
    //             new Edge(0, 1),
    //             new Edge(1, 2),
    //             new Edge(2, 3),
    //             new Edge(3, 0),
    //             new Edge(1, 0),
    //             new Edge(2, 1),
    //             new Edge(3, 2),
    //             new Edge(0, 3)
    //         }
    //     ),
    //     new ElementSet(4, new int[4]{0, 1, 2, 3}),
    //     new EdgeSet(
    //         8,
    //         new Edge*[8]{
    //             new Edge(0, 1),
    //             new Edge(0, 2),
    //             new Edge(2, 3),
    //             new Edge(3, 1),
    //             new Edge(1, 0),
    //             new Edge(2, 0),
    //             new Edge(3, 2),
    //             new Edge(1, 3)
    //         }
    //     ),
    //     true
    // );
    // ok &= testBoundedValenceGraphCanonization(
    //     new ElementSet(3, new int[3]{0, 1, 2}),
    //     new EdgeSet(
    //         2,
    //         new Edge*[2]{
    //             new Edge(0, 1),
    //             new Edge(1, 2)
    //         }
    //     ),
    //     new ElementSet(3, new int[3]{0, 1, 2}),
    //     new EdgeSet(
    //         2,
    //         new Edge*[2]{
    //             new Edge(0, 2),
    //             new Edge(1, 2)
    //         }
    //     ),
    //     false
    // );

    return ok;
}
