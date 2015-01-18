#include "TestElementSet.h"

#include "../../src/types/ElementSet.h"

#include <iostream>

using namespace std;

bool TestElementSet::test() {
    if (!testSubstract()) return false;
    return true;    
}

bool TestElementSet::testSubstract(
    int n, 
    int* elems1, 
    int m, 
    int* elems2, 
    int* result
) {
    ElementSet* elemsSet1 = new ElementSet(n, elems1);
    ElementSet* elemsSet2 = new ElementSet(m, elems2);
    ElementSet* sub = elemsSet1->substract(elemsSet2);

    bool ret = true;
    if (sub->getN() != n - m) ret = false;
    for (int i = 0; ret && i < n - m; ++i)
        if (result[i] != (*sub)[i]) {
            ret = false;
        }

    delete elemsSet1;
    delete elemsSet2;
    delete sub;
    delete[] result;
    return ret;
}

bool TestElementSet::testSubstract() {
    cout << "  Testing ElementSet.substract... ";

    bool ok = true;
    ok &= testSubstract(3, new int[3]{0, 1, 2}, 2, new int[2]{0, 2}, new int[1]{1});
    ok &= testSubstract(
        5,
        new int[5]{0, 1, 2, 6, 7},
        3,
        new int[3]{0, 2, 7},
        new int[2]{1, 6}
    );
    ok &= testSubstract(
        2,
        new int[2]{0, 5},
        1,
        new int[1]{0},
        new int[1]{5}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
