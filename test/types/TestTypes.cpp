#include "TestTypes.h"

#include "TestPermutation.h"
#include "TestElementSet.h"

#include <iostream>

using namespace std;

bool TestTypes::testPermutation() {
    cout << "Testing Permutation" << endl;
    TestPermutation testPerm;
    bool ok = testPerm.test();
    return ok;
}

bool TestTypes::testElementSet() {
    cout << "Testing ElementSet" << endl;
    TestElementSet testElemSet;
    bool ok = testElemSet.test();
    return ok;
}

bool TestTypes::test() {
    if (!testPermutation()) return false;
    if (!testElementSet()) return false;
    return true;
}
