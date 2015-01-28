#include "TestCore.h"

#include "TestStringCanonization.h"
#include "TestBipartiteGraphCanonization.h"

#include <iostream>

using namespace std;

bool TestCore::test() {
    cout << "Testing core..." << endl;
    if (!testStringCanonization()) return false;
    if (!testBipartiteGraphCanonization()) return false;
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

bool TestCore::testBipartiteGraphCanonization() {
    cout << "  Testing bipartiteGraphCanonization... ";
    TestBipartiteGraphCanonization testBipartiteGraphCanonization;
    bool ok = testBipartiteGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
