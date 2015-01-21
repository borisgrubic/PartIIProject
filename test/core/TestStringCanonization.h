#ifndef TEST_STRING_CANONIZATION_H
#define TEST_STRING_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/Permutation.h"
#include "../../src/types/PermutationGroupCoset.h"

#include <string>

using namespace std;

class TestStringCanonization {
    public:
    bool test();

    private:
    bool testStringCanonization(
        string,
        string, 
        ElementSet*, 
        PermutationGroupCoset*,
        string (*inducedAction)(string, Permutation*),
        bool
    );
    bool checkValidityOfResult(
        PermutationGroupCoset*,
        string,
        ElementSet*,
        PermutationGroupCoset*,
        string (*inducedAction)(string, Permutation*)
    );

    static string normalAction(string, Permutation*);
};

#endif
