#include "TestStringCanonization.h"

#include "../../src/core/StringCanonization.h"
#include "../utils/TestUtils.h"

bool TestStringCanonization::checkValidityOfResult(
    PermutationGroupCoset* result,
    ElementSet* str,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*)
) {
    ElementSet* resultStr = 
        (*inducedAction)(str, result->getPermutation(), elems);

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
        ElementSet* curStr = (*inducedAction)(str, curPerm, elems);

        bool ok = true;
        for (int j = 0; j < elems->getN(); ++j)
            if ((*resultStr)[(*elems)[j]] != (*curStr)[(*elems)[j]])
                ok = false;

        delete curStr;
        if (ok) allSamePerms.push_back(curPerm);
        else {
            delete curPerm;
        }
    }

    bool sameGroups = TestUtils::sameGroups(resultGroup, allSamePerms);
    delete resultStr;
    delete tmpGroup;
    delete resultGroup;
    delete allTmpGroup;
    for (int i = 0; i < (int)allSamePerms.size(); ++i) delete allSamePerms[i];
    return sameGroups;
}

bool TestStringCanonization::testStringCanonization(
    ElementSet* str1,
    ElementSet* str2,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*),
    ElementSet* (*getRestrictedString)(ElementSet*, ElementSet*, ElementSet*),
    bool resultsAreSame
) {
    PermutationGroupCoset* result1 = 
        stringCanonization(str1, elems, coset, inducedAction, getRestrictedString, elems);
    PermutationGroupCoset* result2 = 
        stringCanonization(str2, elems, coset, inducedAction, getRestrictedString, elems);

    bool ret = true;
    ret &= checkValidityOfResult(result1, str1, elems, coset, inducedAction);
    ret &= checkValidityOfResult(result2, str2, elems, coset, inducedAction);

    ElementSet* image1 = 
        (*inducedAction)(str1, result1->getPermutation(), elems);
    ElementSet* image2 = 
        (*inducedAction)(str2, result2->getPermutation(), elems);
    bool same = true;
    for (int i = 0; i < elems->getN(); ++i)
        if ((*image1)[(*elems)[i]] != (*image2)[(*elems)[i]])
            same = false;
    ret &= (same == resultsAreSame);

    delete image1;
    delete image2;
    delete str1;
    delete str2;
    delete result1;
    delete result2;
    delete elems;
    delete coset;
    return ret;
}

bool TestStringCanonization::test() {
    bool ok = true;
    ok &= testStringCanonization(
        new ElementSet(2, new int[2]{1, 0}), // "ba"
        new ElementSet(2, new int[2]{0, 1}), // "ab"
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
        &(TestStringCanonization::getRestrictedString),
        true
    );
    ok &= testStringCanonization(
        new ElementSet(3, new int[3]{1, 0, 1}), // "bab",
        new ElementSet(3, new int[3]{0, 1, 0}), // "aba",
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
        &(TestStringCanonization::getRestrictedString),
        true
    );
    ok &= testStringCanonization(
        new ElementSet(7, new int[7]{2, 2, 0, 19, 1, 8, 20}), // "ccatbiu",
        new ElementSet(7, new int[7]{1, 0, 2, 19, 2, 17, 17}), // "bactcqq",
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
        &(TestStringCanonization::getRestrictedString),
        true
    );
    ok &= testStringCanonization(
        new ElementSet(5, new int[5]{0, 1, 0, 2, 3}), // "abacd",
        new ElementSet(5, new int[5]{2, 3, 1, 0, 0}), // "cdbaa",
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
        &(TestStringCanonization::getRestrictedString),
        true
    );
    ok &= testStringCanonization(
        new ElementSet(5, new int[5]{0, 1, 0, 2, 3}), // "abacd",
        new ElementSet(5, new int[5]{2, 3, 1, 0, 1}), // "cdbab",
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
        &(TestStringCanonization::getRestrictedString),
        false
    );

    return ok;
}

ElementSet* TestStringCanonization::normalAction(
    ElementSet* str, 
    Permutation* perm,
    ElementSet* startElems
) {
    (void)startElems;
    ElementSet* ret = new ElementSet(str);
    for (int i = 0; i < perm->getSize(); ++i)
        (*ret)[(*perm)[i]] = (*str)[i];
    return ret;
}

ElementSet* TestStringCanonization::getRestrictedString(
    ElementSet* str,
    ElementSet* elems,
    ElementSet* startElems
) {
    (void)startElems;
    ElementSet* ret = new ElementSet(elems->getN());
    for (int i = 0; i < elems->getN(); ++i) {
        (*ret)[i] = (*str)[(*elems)[i]];
    }
    return ret;
}
