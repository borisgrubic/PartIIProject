#ifndef TEST_GENERAL_GRAPH_CANONIZATION_H
#define TEST_GENERAL_GRAPH_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/EdgeSet.h"

class TestGeneralGraphCanonization {
    public:
    bool test();

    bool testGeneralGraphCanonization(
        ElementSet*,
        EdgeSet*,
        ElementSet*,
        EdgeSet*,
        bool
    );
};

#endif



