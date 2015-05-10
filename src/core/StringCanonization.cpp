#include "StringCanonization.h"

#include "../utils/Utils.h"

#include <assert.h>

PermutationGroupCoset* stringCanonization(
    ElementSet* str,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    ElementSet* (*inducedAction)(ElementSet*, Permutation*, ElementSet*),
    ElementSet* (*getRestrictedString)(ElementSet*, ElementSet*, ElementSet*),
    int (*getImage)(int, Permutation*, ElementSet*),
    ElementSet* startElems
) {
    if (elems->getN() == 1) {
        return new PermutationGroupCoset(coset);
    }

    int n = str->getN();
    ElementSet* orbit = findOrbit(n, (*elems)[0], coset->getGroup(), getImage, startElems);
    bool isTransitive = orbit->getN() == elems->getN();
    if (!isTransitive) {
        ElementSet* rest = elems->substract(orbit);
        PermutationGroupCoset* tmpResult = stringCanonization(
            str,
            orbit,
            coset,
            inducedAction,
            getRestrictedString,
            getImage,
            startElems
        );
        PermutationGroupCoset* result = stringCanonization(
            str,
            rest,
            tmpResult,
            inducedAction,
            getRestrictedString,
            getImage,
            startElems
        );

        delete tmpResult;
        delete orbit;
        delete rest;
        return result;
    } else {
        // coset->getGroup is transitive on elems
        ElementSet* minimalBlockSystem = 
            findMinimalBlockSystem(n, elems, coset->getGroup(), getImage, startElems);
        Permutation** cosetRepresentatives;
        int size;
        PermutationGroup* stabilizer =
            findBlockSystemStabilizer(
                coset->getPermutation()->getSize(),
                elems, 
                minimalBlockSystem, 
                coset->getGroup(),
                &cosetRepresentatives,
                &size,
                getImage,
                startElems
            );

        PermutationGroupCoset** cosets = 
            new PermutationGroupCoset*[size];
        for (int i = 0; i < size; ++i) {
            cosets[i] = new PermutationGroupCoset(
                coset->getPermutation()->compose(cosetRepresentatives[i]),
                new PermutationGroup(stabilizer)
            );
        }
        PermutationGroupCoset** tmpResults = new PermutationGroupCoset*[size];
        for (int i = 0; i < size; ++i) {
            tmpResults[i] = 
                stringCanonization(
                    str, 
                    elems, 
                    cosets[i], 
                    inducedAction,
                    getRestrictedString,
                    getImage,
                    startElems
                );
        }

        ElementSet** tmpStrings = new ElementSet*[size];
        for (int i = 0; i < size; ++i) {
            ElementSet* tmpNonResticted = 
                (*inducedAction)(str, tmpResults[i]->getPermutation(), startElems);
            tmpStrings[i] = getRestrictedString(tmpNonResticted, elems, startElems);
            delete tmpNonResticted;
        }

        int idx = 0;
        int cnt = 1;
        for (int i = 1; i < size; ++i) {
            if ((*tmpStrings[i]) < (*tmpStrings[idx])) {
                idx = i;
                cnt = 1;
            } else if ((*tmpStrings[i]) == (*tmpStrings[idx])) {
                ++cnt;
            }
        }

        assert(idx != -1);
        Permutation** tmpGens = tmpResults[idx]->getGroup()->getGenerators();
        int tmpGensSize = tmpResults[idx]->getGroup()->getGenSize();
        Permutation** generators = 
            new Permutation*[tmpGensSize + cnt];
        for (int i = 0; i < tmpGensSize; ++i) {
            generators[i] = new Permutation(tmpGens[i]);
        }
        int nxt = tmpGensSize;
        Permutation* idxInv = tmpResults[idx]->getPermutation()->getInverse();
        for (int i = idx; i < size; ++i) {
            if ((*tmpStrings[idx]) == (*tmpStrings[i])) {
                generators[nxt++] = 
                    idxInv->compose(tmpResults[i]->getPermutation());
            }
        }

        PermutationGroupCoset* result = new PermutationGroupCoset(
            new Permutation(tmpResults[idx]->getPermutation()),
            new PermutationGroup(tmpGensSize + cnt, generators)
        );

        delete idxInv;
        delete minimalBlockSystem;
        delete stabilizer;
        delete orbit;
        for (int i = 0; i < size; ++i) {
            delete cosets[i];
            delete tmpResults[i];
            delete tmpStrings[i];
            delete cosetRepresentatives[i];
        }
        delete[] cosetRepresentatives;
        delete[] cosets;
        delete[] tmpResults;
        delete[] tmpStrings;
        return result;
    }
}
