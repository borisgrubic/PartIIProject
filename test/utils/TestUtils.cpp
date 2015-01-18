#include "TestUtils.h"

#include "../../src/utils/Utils.h"

#include <iostream>

using namespace std;

bool TestUtils::test() {
    cout << "Testing utils..." << endl;
    if (!testFindOrbit()) return false;
    if (!testFindBlockSystem()) return false;
    if (!testFindMinimalBlockSystem()) return false;
    return true;
}

bool TestUtils::testFindOrbit(
    int n,
    int element,
    PermutationGroup* permGroup,
    int size,
    int* result
) {
    ElementSet* orbit = findOrbit(n, element, permGroup);

    bool ret = true;
    if (size != orbit->getN()) ret = false;
    for (int i = 0; ret && i < size; ++i)
        if ((*orbit)[i] != result[i])
            ret = false;

    delete orbit;
    delete permGroup;
    delete[] result;
    return ret;
}    

bool TestUtils::testFindOrbit() {
    cout << "  Testing findOrbit... ";

    bool ok = true;
    ok &= testFindOrbit(
        5, 
        2, 
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(5, new int[5]{1, 2, 3, 4, 0}),
                new Permutation(5, new int[5]{1, 0, 2, 3, 4})
            }
        ),
        5,
        new int[5]{0, 1, 2, 3, 4}
    );
    ok &= testFindOrbit(
        5,
        4,
        new PermutationGroup(
            1,
            new Permutation*[1]{
                new Permutation(5, new int[5]{1, 0, 2, 3, 4})
            }
        ),
        1,
        new int[1]{4}
    );
    ok &= testFindOrbit(
        5,
        0,
        new PermutationGroup(
            1,
            new Permutation*[1]{
                new Permutation(5, new int[5]{1, 0, 2, 3, 4})
            }
        ),
        2,
        new int[2]{0, 1}
    );
    ok &= testFindOrbit(
        6, 
        3, 
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(6, new int[6]{0, 3, 2, 1, 5, 4}),
                new Permutation(6, new int[6]{1, 0, 2, 3, 4, 5})
            }
        ),
        3,
        new int[3]{0, 1, 3}
    );
    ok &= testFindOrbit(
        6, 
        5, 
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(6, new int[6]{0, 3, 2, 1, 5, 4}),
                new Permutation(6, new int[6]{1, 0, 2, 3, 4, 5})
            }
        ),
        2,
        new int[2]{4, 5}
    );
    ok &= testFindOrbit(
        6, 
        2, 
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(6, new int[6]{0, 3, 2, 1, 5, 4}),
                new Permutation(6, new int[6]{1, 0, 2, 3, 4, 5})
            }
        ),
        1,
        new int[1]{2}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestUtils::testFindBlockSystem(
    int n,
    int idx,
    ElementSet* elems,
    PermutationGroup* group,
    int* result
) {
    ElementSet* blockSystem = findBlockSystem(n, idx, elems, group);

    bool ret = true;
    if (!result && blockSystem) ret = false;
    else if (!blockSystem && result) ret = false;
    else if (blockSystem) {
        for (int i = 0; ret && i < n; ++i)
            if ((*blockSystem)[i] != result[i])
                ret = false;
    }

    delete blockSystem;
    delete elems;
    delete group;
    if (result) {
        delete[] result;
    }
    return ret;
}

bool TestUtils::testFindBlockSystem() {
    cout << "  Testing findBlockSystem... ";

    bool ok = true;
    ok &= testFindBlockSystem(
        5,
        1,
        new ElementSet(5, new int[5]{0, 1, 2, 3, 4}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(5, new int[5]{1, 0, 2, 3, 4}),
                new Permutation(5, new int[5]{1, 2, 3, 4, 0})
            }
        ),
        NULL
    );
    ok &= testFindBlockSystem(
        4,
        2,
        new ElementSet(4, new int[4]{0, 1, 2, 3}),
        new PermutationGroup(
            1,
            new Permutation*[1]{
                new Permutation(4, new int[4]{1, 2, 3, 0})
            }
        ),
        new int[4]{0, 1, 0, 1}
    );
    ok &= testFindBlockSystem(
        4,
        1,
        new ElementSet(4, new int[4]{0, 1, 2, 3}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(4, new int[4]{2, 3, 1, 0}),
                new Permutation(4, new int[4]{0, 1, 3, 2})
            }
        ),
        new int[4]{0, 0, 2, 2}
    );
    ok &= testFindBlockSystem(
        7,
        1,
        new ElementSet(4, new int[4]{0, 1, 2, 3}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(7, new int[7]{2, 3, 1, 0, 6, 4, 5}),
                new Permutation(7, new int[7]{0, 1, 3, 2, 5, 4, 6})
            }
        ),
        new int[7]{0, 0, 2, 2, 4, 5, 6}
    );
    ok &= testFindBlockSystem(
        10,
        6,
        new ElementSet(10, new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(10, new int[10]{1, 2, 3, 4, 0, 6, 7, 8, 9, 5}),
                new Permutation(10, new int[10]{1, 0, 3, 2, 5, 4, 7, 6, 9, 8})
            }
        ),
        new int[10]{0, 1, 2, 3, 4, 4, 0, 1, 2, 3}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

bool TestUtils::testFindMinimalBlockSystem(
    int n,
    ElementSet* elems,
    PermutationGroup* group,
    int* result
) {
    ElementSet* blockSystem = findMinimalBlockSystem(n, elems, group);

    bool ret = true;
    int m = elems->getN();
    if (blockSystem->getN() != m) ret = false;
    for (int i = 0; ret && i < m; ++i)
        if ((*blockSystem)[i] != result[i])
            ret = false;

    delete elems;
    delete group;
    delete blockSystem;
    delete[] result;
    return ret;
}

bool TestUtils::testFindMinimalBlockSystem() {
    cout << "  Testing findMinimalBlockSystem... ";
    
    bool ok = true;
    ok &= testFindMinimalBlockSystem(
        10,
        new ElementSet(10, new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(10, new int[10]{1, 2, 3, 4, 0, 6, 7, 8, 9, 5}),
                new Permutation(10, new int[10]{1, 0, 3, 2, 5, 4, 7, 6, 9, 8})
            }
        ),
        new int[10]{0, 1, 2, 3, 4, 4, 0, 1, 2, 3}
    );
    ok &= testFindMinimalBlockSystem(
        5,
        new ElementSet(5, new int[5]{0, 1, 2, 3, 4}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(5, new int[5]{1, 0, 2, 3, 4}),
                new Permutation(5, new int[5]{1, 2, 3, 4, 0})
            }
        ),
        new int[5]{0, 1, 2, 3, 4}
    );
    ok &= testFindMinimalBlockSystem(
        7,
        new ElementSet(4, new int[4]{0, 1, 2, 4}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(7, new int[7]{2, 4, 1, 3, 0, 4, 5}),
                new Permutation(7, new int[7]{0, 1, 4, 3, 2, 4, 6})
            }
        ),
        new int[4]{0, 0, 2, 2}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return 0;
}
