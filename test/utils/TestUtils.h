#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../../src/types/PermutationGroup.h"
#include "../../src/types/ElementSet.h"

#include <vector>

using namespace std;

class TestUtils {
    public:
    bool test();

    static PermutationGroup* generateGroup(int, PermutationGroup*);
    static bool sameGroups(PermutationGroup*, vector<Permutation*>);

    private:
    bool testFindOrbit();
    bool testFindOrbit(int, int, PermutationGroup*, int, int*);
    bool testFindBlockSystem();
    bool testFindBlockSystem(int, int, ElementSet*, PermutationGroup*, int*);
    bool testFindMinimalBlockSystem();
    bool testFindMinimalBlockSystem(int, ElementSet*, PermutationGroup*, int*);
    bool testFindBlockSystemStabilizer();
    bool testFindBlockSystemStabilizer(int, ElementSet*, PermutationGroup*);
};

#endif
