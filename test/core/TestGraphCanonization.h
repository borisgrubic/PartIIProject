#ifndef TEST_GRAPH_CANONIZATION_H
#define TEST_GRAPH_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/PermutationGroupCoset.h"
#include "../../src/types/EdgeSet.h"

class TestGraphCanonization {
    public:
    bool test();

    static ElementSet* getAdjacencyList(
        ElementSet*,
        EdgeSet*
    );
    private:
    bool testGraphCanonization(
        ElementSet*,
        EdgeSet*,
        ElementSet*,
        EdgeSet*,
        PermutationGroupCoset*,
        bool
    );
    bool checkValidityOfResult(
        PermutationGroupCoset*,
        ElementSet*,
        EdgeSet*
    );
    PermutationGroupCoset* createCoset(int);
};

#endif

