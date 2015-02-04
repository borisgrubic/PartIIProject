#ifndef TEST_STRING_CANONIZATION_H
#define TEST_STRING_CANONIZATION_H

#include "../../src/types/ElementSet.h"
#include "../../src/types/Permutation.h"
#include "../../src/types/PermutationGroupCoset.h"

class TestStringCanonization {
    public:
    bool test();

    static ElementSet* normalAction(ElementSet*, Permutation*, ElementSet*);
    static ElementSet* getRestrictedString(
        ElementSet*, 
        ElementSet*, 
        ElementSet*
    );

    private:
    bool testStringCanonization(
        ElementSet*,
        ElementSet*, 
        ElementSet*, 
        PermutationGroupCoset*,
        ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*),
        ElementSet* (*getRestrictedString)(ElementSet*, ElementSet*, ElementSet*),
        bool
    );
    bool checkValidityOfResult(
        PermutationGroupCoset*,
        ElementSet*,
        ElementSet*,
        PermutationGroupCoset*,
        ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*)
    );
};

#endif
