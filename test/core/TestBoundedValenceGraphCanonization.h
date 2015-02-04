#ifndef TEST_BOUNDED_VALENCE_GRAPH_CANONIZATION_H
#define TEST_BOUNDED_VALENCE_GRAPH_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/EdgeSet.h"

class TestBoundedValenceGraphCanonization {
    public:
    bool test();

    private:
    bool testBoundedValenceGraphCanonization(
        ElementSet*,
        EdgeSet*,
        ElementSet*,
        EdgeSet*,
        bool
    );
};

#endif


