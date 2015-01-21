#include "TestStringCanonization.h"

#include "../../src/core/StringCanonization.h"
#include "../utils/TestUtils.h"

bool TestStringCanonization::checkValidityOfResult(
    PermutationGroupCoset* result,
    string str,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    string (*inducedAction)(string, Permutation*)
) {
    string resultStr = (*inducedAction)(str, result->getPermutation());

    PermutationGroup* tmpGroup = 
        TestUtils::generateGroup(
            result->getPermutation()->getSize(),
            result->getGroup()
        );
    Permutation** allPermutations = new Permutation*[tmpGroup->getGenSize()];
    for (int i = 0; i < tmpGroup->getGenSize(); ++i) {
        allPermutations[i] = 
            result->getPermutation()->compose(tmpGroup->getGenerators()[i]);
    }
    PermutationGroup* resultGroup = 
        new PermutationGroup(tmpGroup->getGenSize(), allPermutations);

    vector<Permutation*> allSamePerms;
    PermutationGroup* allTmpGroup =
        TestUtils::generateGroup(
            coset->getPermutation()->getSize(),
            coset->getGroup()
        );
    for (int i = 0; i < allTmpGroup->getGenSize(); ++i) {
        Permutation* curPerm =
            coset->getPermutation()->compose(allTmpGroup->getGenerators()[i]);
        string curStr = (*inducedAction)(str, curPerm);

        bool ok = true;
        for (int j = 0; j < elems->getN(); ++j)
            if (resultStr[(*elems)[j]] != curStr[(*elems)[j]])
                ok = false;

        if (ok) allSamePerms.push_back(curPerm);
        else {
            delete curPerm;
        }
    }

    bool sameGroups = TestUtils::sameGroups(resultGroup, allSamePerms);
    delete tmpGroup;
    delete resultGroup;
    delete allTmpGroup;
    for (int i = 0; i < (int)allSamePerms.size(); ++i) delete allSamePerms[i];
    return sameGroups;
}

bool TestStringCanonization::testStringCanonization(
    string str1,
    string str2,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    string (*inducedAction)(string, Permutation*),
    bool resultsAreSame
) {
    PermutationGroupCoset* result1 = 
        stringCanonization(str1, elems, coset, inducedAction);
    PermutationGroupCoset* result2 = 
        stringCanonization(str2, elems, coset, inducedAction);

    bool ret = true;
    ret &= checkValidityOfResult(result1, str1, elems, coset, inducedAction);
    ret &= checkValidityOfResult(result2, str2, elems, coset, inducedAction);

    string image1 = (*inducedAction)(str1, result1->getPermutation());
    string image2 = (*inducedAction)(str2, result2->getPermutation());
    bool same = true;
    for (int i = 0; i < elems->getN(); ++i)
        if (image1[(*elems)[i]] != image2[(*elems)[i]])
            same = false;
    ret &= (same == resultsAreSame);

    delete result1;
    delete result2;
    if (resultsAreSame)
        str1 = str2;
    delete elems;
    delete coset;
    return ret;
}

bool TestStringCanonization::test() {
    bool ok = true;
    ok &= testStringCanonization(
        "ba",
        "ab",
        new ElementSet(2, new int[2]{0, 1}),
        new PermutationGroupCoset(
            new Permutation(2),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(2),
                    new Permutation(2, new int[2]{1, 0})
                }
            )
        ),
        &(TestStringCanonization::normalAction),
        true
    );
    ok &= testStringCanonization(
        "bab",
        "aba",
        new ElementSet(2, new int[2]{0, 1}),
        new PermutationGroupCoset(
            new Permutation(3),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(3),
                    new Permutation(3, new int[3]{1, 0, 2})
                }
            )
        ),
        &(TestStringCanonization::normalAction),
        true
    );
    ok &= testStringCanonization(
        "ccatbiu",
        "bactcqq",
        new ElementSet(4, new int[4]{0, 1, 2, 4}),
        new PermutationGroupCoset(
            new Permutation(7),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(7, new int[7]{2, 4, 1, 3, 0, 6, 5}),
                    new Permutation(7, new int[7]{0, 1, 4, 3, 2, 5, 6})
                }
            )
        ),
        &(TestStringCanonization::normalAction),
        true
    );
    ok &= testStringCanonization(
        "abacd",
        "cdbaa",
        new ElementSet(5, new int[5]{0, 1, 2, 3, 4}),
        new PermutationGroupCoset(
            new Permutation(5),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(5, new int[5]{1, 0, 2, 3, 4}),
                    new Permutation(5, new int[5]{1, 2, 3, 4, 0})
                }
            )
        ),
        &(TestStringCanonization::normalAction),
        true
    );
    ok &= testStringCanonization(
        "abacd",
        "cdbab",
        new ElementSet(5, new int[5]{0, 1, 2, 3, 4}),
        new PermutationGroupCoset(
            new Permutation(5),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(5, new int[5]{1, 0, 2, 3, 4}),
                    new Permutation(5, new int[5]{1, 2, 3, 4, 0})
                }
            )
        ),
        &(TestStringCanonization::normalAction),
        false
    );

    return ok;
}

string TestStringCanonization::normalAction(string str, Permutation* perm) {
    string ret = str;
    for (int i = 0; i < perm->getSize(); ++i)
        ret[(*perm)[i]] = str[i];
    return ret;
}
