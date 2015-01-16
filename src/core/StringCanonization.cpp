#include "StringCanonization.h"

#include "../utils/Utils.h"

#include <assert.h>
#include <string.h>

PermutationGroupCoset* stringCanonization(
    string str,
    ElementSet* elems,
    PermutationGroupCoset* coset,
    string (*inducedAction)(string, Permutation)
) {
    if (elems->getN() == 1) {
        return coset;
    }

    ElementSet* orbit = findOrbit(str.size(), (*elems)[0], coset->getGroup());
    bool isTransitive = orbit->getN() == elems->getN();
    if (!isTransitive) {
        ElementSet* rest = elems->substract(orbit);
        PermutationGroupCoset* tmpResult = stringCanonization(
            str,
            orbit,
            coset,
            inducedAction
        );
        PermutationGroupCoset* result = stringCanonization(
            str,
            rest,
            tmpResult,
            inducedAction
        );

        delete tmpResult;
        delete orbit;
        delete rest;
        return result;
    } else {
        // coset->getGroup is transitive on elems
        ElementSet* minimalBlockSystem = 
            findMinimalBlockSystem(str.size(), elems, coset->getGroup());
        Permutation** cosetRepresentatives;
        int size;
        PermutationGroup* stabilizer =
            findBlockSystemStabilizer(
                str.size(),
                elems, 
                minimalBlockSystem, 
                coset->getGroup(),
                &cosetRepresentatives,
                &size
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
                stringCanonization(str, elems, cosets[i], inducedAction);
        }

        char** tmpStrings = new char*[size];
        for (int i = 0; i < size; ++i) {
            string changedStr = 
                (*inducedAction)(str, tmpResults[i]->getPermutation());
            tmpStrings[i] = new char[elems->getN() + 1];
            tmpStrings[i][elems->getN()] = '\0';
            for (int j = 0; j < elems->getN(); ++j) {
                tmpStrings[i][j] = changedStr[(*elems)[j]];
            }
        }

        int idx = -1;
        int cnt = 0;
        for (int i = 0; i < size; ++i) {
            int cmpRes = 1;
            if (idx != -1) {
                cmpRes = strcmp(tmpStrings[idx], tmpStrings[i]);
            }
            if (cmpRes > 0) {
                idx = i;
                cnt = 1;
            } else if (cmpRes == 0) {
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
        for (int i = idx + 1; i < size; ++i) {
            if (strcmp(tmpStrings[idx], tmpStrings[i]) == 0) {
                generators[nxt++] = 
                    idxInv->compose(tmpResults[i]->getPermutation());
            }
        }

        PermutationGroupCoset* result = new PermutationGroupCoset(
            new Permutation(tmpResults[idx]->getPermutation()),
            new PermutationGroup(tmpGensSize + cnt, generators)
        );

        delete minimalBlockSystem;
        delete stabilizer;
        delete orbit;
        for (int i = 0; i < size; ++i) {
            delete cosets[i];
            delete tmpResults[i];
            delete[] tmpStrings[i];
        }
        delete[] cosets;
        delete[] tmpResults;
        delete[] tmpStrings;
        return result;
    }
}
