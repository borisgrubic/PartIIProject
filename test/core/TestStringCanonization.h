#ifndef TEST_STRING_CANONIZATION_H
#define TEST_STRING_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/Permutation.h"
#include "../../src/types/PermutationGroupCoset.h"

class TestStringCanonization {
    public:
    bool test();

    static ElementSet* normalAction(ElementSet*, Permutation*);

    private:
    bool testStringCanonization(
        ElementSet*,
        ElementSet*, 
        ElementSet*, 
        PermutationGroupCoset*,
        ElementSet* (*inducedAction)(ElementSet*, Permutation*),
        bool
    );
    bool checkValidityOfResult(
        PermutationGroupCoset*,
        ElementSet*,
        ElementSet*,
        PermutationGroupCoset*,
        ElementSet* (*inducedAction)(ElementSet*, Permutation*)
    );
};

#endif
