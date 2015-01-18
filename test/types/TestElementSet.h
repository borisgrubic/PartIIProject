#ifndef TEST_ELEMENT_SET_H
#define TEST_ELEMENT_SET_H

class TestElementSet {
    public:
    bool test();

    private:
    bool testSubstract();
    bool testSubstract(int, int*, int, int*, int*);
};

#endif
