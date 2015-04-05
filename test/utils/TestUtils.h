#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../../src/types/PermutationGroup.h"
#include "../../src/types/ElementSet.h"
#include "../../src/types/EdgeSet.h"

#include <vector>

using namespace std;

class TestUtils {
    public:
    bool test();

    static PermutationGroup* generateGroup(int, PermutationGroup*);
    static bool sameGroups(PermutationGroup*, vector<Permutation*>);

    private:
    bool testFindOrbit();
    bool testFindOrbit(int, int, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*, int, int*);
    bool testFindBlockSystem();
    bool testFindBlockSystem(int, int, ElementSet*, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*, int*);
    bool testFindMinimalBlockSystem();
    bool testFindMinimalBlockSystem(int, ElementSet*, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*, int*);
    bool testFindBlockSystemStabilizer();
    bool testFindBlockSystemStabilizer(int, ElementSet*, PermutationGroup*, int (*getImage)(int, Permutation*, ElementSet*), ElementSet*);
    bool testBinom();
    bool testFindSubset(int, int, ElementSet*);
    bool testFindSubset();
    bool testFindSubsetIdx();
    bool testFindSubsetIdx(int*, int, int, int);
    bool testNaiveRefinement();
    bool testNaiveRefinement(ElementSet*, EdgeSet*, int*, int*, bool);
    bool testNextSubset();
    bool testNextSubset(int, int*, int, int*);
};

#endif
