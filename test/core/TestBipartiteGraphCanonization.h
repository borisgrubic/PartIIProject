#ifndef TEST_BIPARTITE_GRAPH_CANONIZATION_H
#define TEST_BIPARTITE_GRAPH_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/PermutationGroupCoset.h"
#include "../../src/types/EdgeSet.h"

class TestBipartiteGraphCanonization {
    public:
    bool test();

    private:
    bool testBipartiteGraphCanonization(
        ElementSet*,
        ElementSet*,
        EdgeSet*,
        ElementSet*,
        ElementSet*,
        EdgeSet*,
        PermutationGroupCoset*,
        bool
    );
};

#endif

