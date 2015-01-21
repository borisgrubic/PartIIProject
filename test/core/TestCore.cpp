#include "TestCore.h"

#include "TestStringCanonization.h"

#include <iostream>

using namespace std;

bool TestCore::test() {
    cout << "Testing core..." << endl;
    if (!testStringCanonization()) return false;
    return true;
}

bool TestCore::testStringCanonization() {
    cout << "  Testing stringCanonization... ";
    TestStringCanonization testStringCanonization;
    bool ok = testStringCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
