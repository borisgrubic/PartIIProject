#include "TestGeneralGraphCanonization.h"

#include "../../src/core/GraphCanonization.h"
#include "../../src/core/GeneralGraphCanonization.h"
#include "../../src/types/PermutationGroupCoset.h"
#include "../../src/utils/Utils.h"

bool TestGeneralGraphCanonization::testGeneralGraphCanonization(
    ElementSet* nodes1,
    EdgeSet* edges1,
    ElementSet* nodes2,
    EdgeSet* edges2,
    bool resultsAreSame
) {
    ElementSet* result1 = generalGraphCanonization(nodes1, edges1);
    ElementSet* result2 = generalGraphCanonization(nodes2, edges2);
    bool ret = (resultsAreSame == (*result1 == *result2));
    delete result1;
    delete result2;
    delete nodes1;
    delete edges1;
    delete nodes2;
    delete edges2;
    return ret;
}

bool TestGeneralGraphCanonization::test() {
    bool ok = true;
    ok &= testGeneralGraphCanonization(
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
    ok &= testGeneralGraphCanonization(
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
    ok &= testGeneralGraphCanonization(
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
    ok &= testGeneralGraphCanonization(
        new ElementSet(6, new int[6]{0, 1, 2, 3, 4, 5}),
        new EdgeSet(
            18,
            new Edge*[18]{
                new Edge(0, 1),
                new Edge(1, 2),
                new Edge(2, 3),
                new Edge(3, 4),
                new Edge(4, 5),
                new Edge(5, 0),
                new Edge(0, 3),
                new Edge(1, 4),
                new Edge(2, 5),
                new Edge(1, 0),
                new Edge(2, 1),
                new Edge(3, 2),
                new Edge(4, 3),
                new Edge(5, 4),
                new Edge(0, 5),
                new Edge(3, 0),
                new Edge(4, 1),
                new Edge(5, 2)
            }
        ),
        new ElementSet(6, new int[6]{0, 1, 2, 3, 4, 5}),
        new EdgeSet(
            18,
            new Edge*[18]{
                new Edge(0, 3),
                new Edge(0, 4),
                new Edge(0, 5),
                new Edge(1, 3),
                new Edge(1, 4),
                new Edge(1, 5),
                new Edge(2, 3),
                new Edge(2, 4),
                new Edge(2, 5),
                new Edge(3, 0),
                new Edge(4, 0),
                new Edge(5, 0),
                new Edge(3, 1),
                new Edge(4, 1),
                new Edge(5, 1),
                new Edge(3, 2),
                new Edge(4, 2),
                new Edge(5, 2),
            }
        ),
        true
    );
    ok &= testGeneralGraphCanonization(
        new ElementSet(8, new int[8]{0, 1, 2, 3, 4, 5, 6, 7}),
        new EdgeSet(
            24,
            new Edge*[24]{
                new Edge(0, 4),
                new Edge(0, 5),
                new Edge(0, 6),
                new Edge(1, 4),
                new Edge(1, 5),
                new Edge(1, 7),
                new Edge(2, 4),
                new Edge(2, 6),
                new Edge(2, 7),
                new Edge(3, 5),
                new Edge(3, 6),
                new Edge(3, 7),
                new Edge(4, 0),
                new Edge(5, 0),
                new Edge(6, 0),
                new Edge(4, 1),
                new Edge(5, 1),
                new Edge(7, 1),
                new Edge(4, 2),
                new Edge(6, 2),
                new Edge(7, 2),
                new Edge(5, 3),
                new Edge(6, 3),
                new Edge(7, 3)
            }
        ),
        new ElementSet(8, new int[8]{0, 1, 2, 3, 4, 5, 6, 7}),
        new EdgeSet(
            24,
            new Edge*[24]{
                new Edge(0, 1),
                new Edge(1, 2),
                new Edge(2, 3),
                new Edge(3, 0),
                new Edge(4, 5),
                new Edge(5, 6),
                new Edge(6, 7),
                new Edge(7, 4),
                new Edge(0, 4),
                new Edge(1, 5),
                new Edge(2, 6),
                new Edge(3, 7),
                new Edge(1, 0),
                new Edge(2, 1),
                new Edge(3, 2),
                new Edge(0, 3),
                new Edge(5, 4),
                new Edge(6, 5),
                new Edge(7, 6),
                new Edge(4, 7),
                new Edge(4, 0),
                new Edge(5, 1),
                new Edge(6, 2),
                new Edge(7, 3)
            }
        ),
        true
    );
    ok &= testGeneralGraphCanonization(
        new ElementSet(6, new int[8]{0, 1, 2, 3, 4, 5}),
        new EdgeSet(
            11,
            new Edge*[11]{
                new Edge(0, 4),
                new Edge(1, 0),
                new Edge(2, 5),
                new Edge(3, 1),
                new Edge(3, 2),
                new Edge(4, 0),
                new Edge(4, 2),
                new Edge(4, 3),
                new Edge(5, 1),
                new Edge(5, 3),
                new Edge(5, 4),
            }
        ),
        new ElementSet(6, new int[8]{0, 1, 2, 3, 4, 5}),
        new EdgeSet(
            11,
            new Edge*[11]{
                new Edge(0, 2),
                new Edge(0, 3),
                new Edge(0, 5),
                new Edge(1, 3),
                new Edge(2, 1),
                new Edge(3, 1),
                new Edge(3, 4),
                new Edge(3, 5),
                new Edge(4, 0),
                new Edge(5, 2),
                new Edge(5, 4),
            }
        ),
        true
    );

    return ok;
}

