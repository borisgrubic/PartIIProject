#ifndef TEST_GRAPH_CANONIZATION_H
#define TEST_GRAPH_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/PermutationGroupCoset.h"
#include "../../src/types/EdgeSet.h"

class TestGraphCanonization {
    public:
    bool test();

    private:
    bool testGraphCanonization(
        ElementSet*,
        EdgeSet*,
        ElementSet*,
        EdgeSet*,
        bool
    );
    bool checkValidityOfResult(
        PermutationGroupCoset*,
        ElementSet*,
        EdgeSet*
    );
    ElementSet* getAdjacencyList(
        ElementSet*,
        EdgeSet*
    );
};

#endif

