#include "TestCore.h"

#include "TestStringCanonization.h"
#include "TestBipartiteGraphCanonization.h"
#include "TestGraphCanonization.h"
#include "TestBoundedValenceGraphCanonization.h"
#include "TestGeneralGraphCanonization.h"
#include "TestGeneralGraphCanonizationBrute.h"

#include <iostream>

using namespace std;

bool TestCore::test() {
    cout << "Testing core..." << endl;
    if (!testStringCanonization()) return false;
    if (!testBipartiteGraphCanonization()) return false;
    if (!testGraphCanonization()) return false;
    if (!testBoundedValenceGraphCanonization()) return false;
    if (!testGeneralGraphCanonization()) return false;
    /* if (!testGeneralGraphCanonizationBrute()) return false; */
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

bool TestCore::testGraphCanonization() {
    cout << "  Testing graphCanonization... ";
    TestGraphCanonization testGraphCanonization;
    bool ok = testGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testBoundedValenceGraphCanonization() {
    cout << "  Testing boundedGraphCanonization... ";
    TestBoundedValenceGraphCanonization testBoundedValenceGraphCanonization;
    bool ok = testBoundedValenceGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testGeneralGraphCanonization() {
    cout << "  Testing generalGraphCanonization... ";
    TestGeneralGraphCanonization testGeneralGraphCanonization;
    bool ok = testGeneralGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testGeneralGraphCanonizationBrute() {
    cout << "  Testing generalGraphCanonizationBrute... ";
    TestGeneralGraphCanonizationBrute testGeneralGraphCanonizationBrute;
    bool ok = testGeneralGraphCanonizationBrute.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
