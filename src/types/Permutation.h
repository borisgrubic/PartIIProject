#ifndef PERMUTATION_H
#define PERMUTATION_H

class Permutation {
    private:
    int size;
    int* perm;

    public:
    Permutation(int);
    Permutation(Permutation*);
    Permutation(int, int*);
    ~Permutation();
    int getSize();
    int* getPermutation();
    int& operator[](const int);
    Permutation* getInverse();
    Permutation* compose(Permutation*);
};

#endif
