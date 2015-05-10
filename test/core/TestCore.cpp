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
    cout << "Testing core" << endl;
    if (!testStringCanonization()) return false;
    if (!testBipartiteGraphCanonization()) return false;
    if (!testGraphCanonization()) return false;
    if (!testBoundedValenceGraphCanonization()) return false;
    if (!testGeneralGraphCanonization()) return false;
    if (!testGeneralGraphCanonizationBrute()) return false;
    return true;
}

bool TestCore::testStringCanonization() {
    string msg = "  Testing stringCanonization ";
    msg.resize(41, ' ');
    cout << msg;

    TestStringCanonization testStringCanonization;
    bool ok = testStringCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testBipartiteGraphCanonization() {
    string msg = "  Testing bipartiteGraphCanonization ";
    msg.resize(41, ' ');
    cout << msg;

    TestBipartiteGraphCanonization testBipartiteGraphCanonization;
    bool ok = testBipartiteGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testGraphCanonization() {
    string msg = "  Testing graphCanonization ";
    msg.resize(41, ' ');
    cout << msg;

    TestGraphCanonization testGraphCanonization;
    bool ok = testGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testBoundedValenceGraphCanonization() {
    string msg = "  Testing boundedGraphCanonization ";
    msg.resize(41, ' ');
    cout << msg;

    TestBoundedValenceGraphCanonization testBoundedValenceGraphCanonization;
    bool ok = testBoundedValenceGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testGeneralGraphCanonization() {
    string msg = "  Testing generalGraphCanonization ";
    msg.resize(41, ' ');
    cout << msg;

    TestGeneralGraphCanonization testGeneralGraphCanonization;
    bool ok = testGeneralGraphCanonization.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestCore::testGeneralGraphCanonizationBrute() {
    string msg = "  Testing generalGraphCanonizationBrute ";
    msg.resize(41, ' ');
    cout << msg;

    TestGeneralGraphCanonizationBrute testGeneralGraphCanonizationBrute;
    bool ok = testGeneralGraphCanonizationBrute.test();
    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
