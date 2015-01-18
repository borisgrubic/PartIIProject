#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../../src/types/PermutationGroup.h"
#include "../../src/types/ElementSet.h"

class TestUtils {
    public:
    bool test();

    private:
    bool testFindOrbit();
    bool testFindOrbit(int, int, PermutationGroup*, int, int*);
    bool testFindBlockSystem();
    bool testFindBlockSystem(int, int, ElementSet*, PermutationGroup*, int*);
    bool testFindMinimalBlockSystem();
    bool testFindMinimalBlockSystem(int, ElementSet*, PermutationGroup*, int*);
};

#endif
