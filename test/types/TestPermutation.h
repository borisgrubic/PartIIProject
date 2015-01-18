#ifndef TEST_PERMUTATION_H
#define TEST_PERMUTATION_H

class TestPermutation {
    public:
    bool test();

    private:
    bool testGetInverse();
    bool testGetInverse(int, int*, int*);
    bool testCompose();
    bool testCompose(int n, int*, int*, int*);
};

#endif
