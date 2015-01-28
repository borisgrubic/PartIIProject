#ifndef ELEMENT_SET_H
#define ELEMENT_SET_H

class ElementSet {
    private:
    int n;
    int* elems;

    public:
    ElementSet(int);
    ElementSet(ElementSet*);
    ElementSet(int, int*);
    ~ElementSet();
    int getN();
    int* getElems();
    int& operator[](const int);
    bool operator==(ElementSet&);
    bool operator<(ElementSet&);
    int find(int);
    ElementSet* substract(ElementSet*);
};

#endif
