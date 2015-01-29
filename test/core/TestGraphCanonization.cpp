#include "TestGraphCanonization.h"

#include "../../src/core/GraphCanonization.h"
#include "../utils/TestUtils.h"

#include <vector>
#include <algorithm>

ElementSet* TestGraphCanonization::getAdjacencyList(
    ElementSet* nodes,
    EdgeSet* edges
) {
    int n = nodes->getN();
    int* adjacencyList = new int[n * n];
    for (int i = 0; i < n * n; ++i) adjacencyList[i] = 0;
    for (int i = 0; i < edges->getN(); ++i) {
        int from = (*edges)[i]->getFrom();
        int dest = (*edges)[i]->getDest();
        adjacencyList[from * n + dest] = 1;
    }
    return new ElementSet(n * n, adjacencyList);
}

bool TestGraphCanonization::checkValidityOfResult(
    PermutationGroupCoset* result,
    ElementSet* nodes,
    EdgeSet* edges
) {
    PermutationGroup* tmpGroup =
        TestUtils::generateGroup(
            result->getPermutation()->getSize(),
            result->getGroup()
        );
    Permutation** allPermutations = new Permutation*[tmpGroup->getGenSize()];
    for (int i = 0; i < tmpGroup->getGenSize(); ++i) {
        allPermutations[i] = 
            result->getPermutation()->compose(tmpGroup->getGenerators()[i]);
    }
    PermutationGroup* resultGroup = 
        new PermutationGroup(tmpGroup->getGenSize(), allPermutations);

    vector<Permutation*> allSamePerms;
    ElementSet* str = getAdjacencyList(nodes, edges);
    ElementSet* resultStr = graphInducedAction(str, result->getPermutation());
    int n = nodes->getN();
    int* curPermArray = new int[n];
    for (int i = 0; i < n; ++i) curPermArray[i] = i;
    Permutation* curPerm = new Permutation(n, curPermArray);
    do {
        ElementSet* curStr = graphInducedAction(str, curPerm);

        bool ok = (*curStr) == (*resultStr);

        delete curStr;
        if (ok) allSamePerms.push_back(new Permutation(curPerm));
    } while (next_permutation(curPermArray, curPermArray + n));

    bool sameGroups = TestUtils::sameGroups(resultGroup, allSamePerms);
    delete tmpGroup;
    delete resultGroup;
    delete str;
    delete resultStr;
    delete curPerm;
    for (int i = 0; i < (int)allSamePerms.size(); ++i) delete allSamePerms[i];
    return sameGroups;
}

bool TestGraphCanonization::testGraphCanonization(
    ElementSet* nodes1,
    EdgeSet* edges1,
    ElementSet* nodes2,
    EdgeSet* edges2,
    bool resultsAreSame
) {
    PermutationGroupCoset* result1 = graphCanonization(nodes1, edges1);
    PermutationGroupCoset* result2 = graphCanonization(nodes2, edges2);

    bool ret = true;
    // ret &= checkValidityOfResult(result1, nodes1, edges1);
    // ret &= checkValidityOfResult(result2, nodes2, edges2);

    ElementSet* adjacencyList1 = getAdjacencyList(nodes1, edges1);
    ElementSet* adjacencyList2 = getAdjacencyList(nodes2, edges2);
    ElementSet* finalGraph1 = 
        graphInducedAction(adjacencyList1, result1->getPermutation());
    ElementSet* finalGraph2 = 
        graphInducedAction(adjacencyList2, result2->getPermutation());

    ret &= (resultsAreSame == ((*finalGraph1) == (*finalGraph2)));

    delete nodes1;
    delete edges1;
    delete nodes2;
    delete edges2;
    delete result1;
    delete result2;
    delete adjacencyList1;
    delete adjacencyList2;
    delete finalGraph1;
    delete finalGraph2;
    return ret;
}

bool TestGraphCanonization::test() {
    bool ok = true;
    ok &= testGraphCanonization(
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
    ok &= testGraphCanonization(
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
                new Edge(1, 2)
            }
        ),
        false
    );
    ok &= testGraphCanonization(
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
            3,
            new Edge*[3]{
                new Edge(0, 1),
                new Edge(1, 2),
                new Edge(2, 0)
            }
        ),
        false
    );
    ok &= testGraphCanonization(
        new ElementSet(4, new int[4]{0, 1, 2, 3}),
        new EdgeSet(
            8,
            new Edge*[8]{
                new Edge(0, 1),
                new Edge(1, 2),
                new Edge(2, 3),
                new Edge(3, 0),
                new Edge(1, 0),
                new Edge(2, 1),
                new Edge(3, 2),
                new Edge(0, 3)
            }
        ),
        new ElementSet(4, new int[4]{0, 1, 2, 3}),
        new EdgeSet(
            8,
            new Edge*[8]{
                new Edge(0, 1),
                new Edge(0, 2),
                new Edge(2, 3),
                new Edge(3, 1),
                new Edge(1, 0),
                new Edge(2, 0),
                new Edge(3, 2),
                new Edge(1, 3)
            }
        ),
        true
    );
    // ok &= testGraphCanonization(
    //     new ElementSet(6, new int[6]{0, 1, 2, 3, 4, 5}),
    //     new EdgeSet(
    //         18,
    //         new Edge*[18]{
    //             new Edge(0, 3),
    //             new Edge(0, 4),
    //             new Edge(0, 5),
    //             new Edge(1, 3),
    //             new Edge(1, 4),
    //             new Edge(1, 5),
    //             new Edge(2, 3),
    //             new Edge(2, 4),
    //             new Edge(2, 5),
    //             new Edge(3, 0),
    //             new Edge(4, 0),
    //             new Edge(5, 0),
    //             new Edge(3, 1),
    //             new Edge(4, 1),
    //             new Edge(5, 1),
    //             new Edge(3, 2),
    //             new Edge(4, 2),
    //             new Edge(5, 2),
    //         }
    //     ),
    //     new ElementSet(6, new int[6]{0, 1, 2, 3, 4, 5}),
    //     new EdgeSet(
    //         18,
    //         new Edge*[18]{
    //             new Edge(0, 1),
    //             new Edge(1, 2),
    //             new Edge(2, 3),
    //             new Edge(3, 4),
    //             new Edge(4, 5),
    //             new Edge(5, 0),
    //             new Edge(0, 3),
    //             new Edge(1, 4),
    //             new Edge(2, 5),
    //             new Edge(1, 0),
    //             new Edge(2, 1),
    //             new Edge(3, 2),
    //             new Edge(4, 3),
    //             new Edge(5, 4),
    //             new Edge(0, 5),
    //             new Edge(3, 0),
    //             new Edge(4, 1),
    //             new Edge(5, 2)
    //         }
    //     ),
    //     true
    // );

    return ok;
}
