#ifndef TEST_CORE_H
#define TEST_CORE_H

class TestCore {
    public:
    bool test();

    private:
    bool testStringCanonization();
    bool testBipartiteGraphCanonization();
    bool testGraphCanonization();
    bool testBoundedValenceGraphCanonization();
};

#endif
