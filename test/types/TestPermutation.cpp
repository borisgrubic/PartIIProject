#include "TestPermutation.h"

#include "../../src/types/Permutation.h"

#include <iostream>

using namespace std;

bool TestPermutation::test() {
    if (!testGetInverse()) return false;
    if (!testCompose()) return false;
    return true;
}

bool TestPermutation::testGetInverse(int n, int* permArray, int* result) {
    Permutation* perm = new Permutation(n, permArray);
    Permutation* inv = perm->getInverse();
    
    bool ret = true;
    if (n != inv->getSize()) ret = false;
    for (int i = 0; ret && i < n; ++i)
        if ((*inv)[i] != result[i])
            ret = false;

    delete perm;
    delete inv;
    delete[] result;
    return ret;
}

bool TestPermutation::testGetInverse() {
    string msg = "  Testing Permutation.getInverse ";
    msg.resize(41, ' ');
    cout << msg;

    bool ok = true;
    ok &= testGetInverse(5, new int[5]{4, 0, 2, 1, 3}, new int[5]{1, 3, 2, 4, 0});
    ok &= testGetInverse(1, new int[1]{0}, new int[1]{0});
    ok &= testGetInverse(3, new int[3]{2, 1, 0}, new int[3]{2, 1, 0});

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestPermutation::testCompose(int n, int* perm1Array, int* perm2Array, int* result) {
    Permutation* perm1 = new Permutation(n, perm1Array);
    Permutation* perm2 = new Permutation(n, perm2Array);
    Permutation* comp = perm1->compose(perm2);

    bool ret = true;
    if (n != comp->getSize()) ret = false;
    for (int i = 0; ret && i < n; ++i)
        if ((*comp)[i] != result[i])
            ret = false;

    delete perm1;
    delete perm2;
    delete comp;
    delete[] result;
    return ret;
}

bool TestPermutation::testCompose() {
    string msg = "  Testing Permutation.compose ";
    msg.resize(41, ' ');
    cout << msg;

    bool ok = true;
    ok &= testCompose(1, new int[1]{0}, new int[1]{0}, new int[1]{0});
    ok &= testCompose(2, new int[2]{1, 0}, new int[2]{1, 0}, new int[2]{0, 1});
    ok &= testCompose(
        5, 
        new int[5]{4, 3, 2, 1, 0}, 
        new int[5]{1, 3, 0, 2, 4}, 
        new int[5]{4, 2, 0, 3, 1}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
