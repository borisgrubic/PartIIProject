#include "TestUtils.h"

#include "../../src/utils/Utils.h"

#include <iostream>
#include <vector>

using namespace std;

bool TestUtils::test() {
    cout << "Testing utils..." << endl;
    if (!testFindOrbit()) return false;
    if (!testFindBlockSystem()) return false;
    if (!testFindMinimalBlockSystem()) return false;
    if (!testFindBlockSystemStabilizer()) return false;
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
                new Permutation(7, new int[7]{2, 4, 1, 3, 0, 6, 5}),
                new Permutation(7, new int[7]{0, 1, 4, 3, 2, 5, 6})
            }
        ),
        new int[4]{0, 0, 2, 2}
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}

PermutationGroup* TestUtils::generateGroup(int n, PermutationGroup* group) {
    vector<Permutation*> stack;
    vector<Permutation*> ret;
    for (int i = 0; i < group->getGenSize(); ++i) {
        bool marked = false;
        for (int j = 0; j < (int)ret.size(); ++j) {
            bool same = true;
            for (int k = 0; k < n; ++k)
                if ((*ret[j])[k] != (*(group->getGenerators()[j]))[k])
                    same = false;
            if (same) marked = true;
        }
        if (!marked) {
            ret.push_back(new Permutation(group->getGenerators()[i]));
            stack.push_back(ret[0]);
        }
    }

    while (!stack.empty()) {
        Permutation* perm = stack.back();
        stack.pop_back();

        for (int i = 0; i < group->getGenSize(); ++i) {
            Permutation* newPerm = perm->compose(group->getGenerators()[i]);

            bool seen = false;
            for (int j = 0; j < (int)ret.size(); ++j) {
                Permutation* curPerm = ret[j];
                bool same = true;
                for (int k = 0; k < n; ++k)
                    if ((*curPerm)[k] != (*newPerm)[k]) {
                        same = false;
                    }
                if (same) {
                    seen = true;
                    break;
                }
            }

            if (!seen) {
                ret.push_back(newPerm);
                stack.push_back(newPerm);
            } else {
                delete newPerm;
            }
        }
    }

    Permutation** permArray = new Permutation*[ret.size()];
    for (int i = 0; i < (int)ret.size(); ++i)
       permArray[i] = ret[i]; 
    return new PermutationGroup(ret.size(), permArray);
}

bool TestUtils::sameGroups(
    PermutationGroup* group1,
    vector<Permutation*> group2
) {
    bool ret = true;
    if (group1->getGenSize() != (int)group2.size()) ret = false;
    else {
        for (int i = 0; i < (int)group2.size(); ++i) {
            Permutation* perm1 = group2[i];

            bool found = false;
            for (int j = 0; j < (int)group2.size(); ++j) {
                Permutation* perm2 = group1->getGenerators()[j];
                bool same = true;
                for (int k = 0; k < perm1->getSize(); ++k) {
                    if ((*perm1)[k] != (*perm2)[k]) {
                        same = false;
                    }
                }
                if (same) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                ret = false;
            }
        } 
    }
    
    return ret;
}

bool TestUtils::testFindBlockSystemStabilizer(
    int n,
    ElementSet* elems,
    PermutationGroup* group
) {
    Permutation** cosetRepresentatives;
    int size;
    ElementSet* blockSystem = findMinimalBlockSystem(n, elems, group);
    PermutationGroup* stabilizer =
        findBlockSystemStabilizer(
            n, 
            elems,
            blockSystem,
            group,
            &cosetRepresentatives,
            &size
        );
    
    PermutationGroup* group1 = TestUtils::generateGroup(n, group);
    PermutationGroup* group2 = TestUtils::generateGroup(n, stabilizer);
    int m = group1->getGenSize();
    vector<Permutation*> result;
    for (int i = 0; i < m; ++i) {
        Permutation* perm = group1->getGenerators()[i];
        bool ok = true;
        int elemsNum = elems->getN();
        for (int j = 0; j < elemsNum; ++j) {
            int image = -1;
            for (int k = 0; k < elems->getN(); ++k)
                if ((*perm)[(*elems)[j]] == (*elems)[k]) {
                    image = k;
                    break;
                }
            if (image == -1) ok = false;
            else {
                if ((*blockSystem)[j] != (*blockSystem)[image]) {
                    ok = false;
                }
            }
        }
        if (ok) {
            result.push_back(perm);
        }
    }

    bool ret = true;
    if (!TestUtils::sameGroups(group2, result)) ret = false;

    vector<Permutation*> cosetUnion;
    for (int i = 0; i < size; ++i) {
        Permutation** cosetGroup = new Permutation*[group2->getGenSize()];
        for (int j = 0; j < group2->getGenSize(); ++j) {
            cosetGroup[j] = 
                cosetRepresentatives[i]->compose(group2->getGenerators()[j]);
        }
        PermutationGroup* cosetAll = 
            new PermutationGroup(group2->getGenSize(), cosetGroup);
        for (int j = 0; j < cosetAll->getGenSize(); ++j) {
            cosetUnion.push_back(new Permutation(cosetAll->getGenerators()[j]));
        }
        delete cosetAll;
    }

    if (!TestUtils::sameGroups(group1, cosetUnion)) ret = false;

    for (int i = 0; i < (int)cosetUnion.size(); ++i) delete cosetUnion[i];
    delete elems;
    delete group;
    delete blockSystem;
    delete stabilizer;
    delete group1;
    delete group2;
    for (int i = 0; i < size; ++i) delete cosetRepresentatives[i];
    delete[] cosetRepresentatives;
    return ret;
}
     

bool TestUtils::testFindBlockSystemStabilizer() {
    cout << "  Testing findBlockSystemStabilizer... ";

    bool ok = true;
    ok &= testFindBlockSystemStabilizer(
        7,
        new ElementSet(4, new int[4]{0, 1, 2, 4}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(7, new int[7]{2, 4, 1, 3, 0, 6, 5}),
                new Permutation(7, new int[7]{0, 1, 4, 3, 2, 5, 6})
            }
        )
    );
    ok &= testFindBlockSystemStabilizer(
        10,
        new ElementSet(10, new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(10, new int[10]{1, 2, 3, 4, 0, 6, 7, 8, 9, 5}),
                new Permutation(10, new int[10]{1, 0, 3, 2, 5, 4, 7, 6, 9, 8})
            }
        )
    );
    ok &= testFindBlockSystemStabilizer(
        5,
        new ElementSet(5, new int[5]{0, 1, 2, 3, 4}),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(5, new int[5]{1, 0, 2, 3, 4}),
                new Permutation(5, new int[5]{1, 2, 3, 4, 0})
            }
        )
    );

    if (ok) cout << "OK!" << endl;
    else cout << "Fail!" << endl;
    return ok;
}
