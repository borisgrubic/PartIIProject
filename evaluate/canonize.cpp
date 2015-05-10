#include "../src/core/GeneralGraphCanonization.h"
#include "../src/types/ElementSet.h"
#include "../src/types/Edge.h"

#include <iostream>
#include <cstdio>

using namespace std;

int main(int argv, char* argc[]) {
    if (argv != 2) {
        return -1;
    }

    FILE* fin = fopen(argc[1], "r");
    int n, m;
    char str[10]; char ch;
    fscanf(fin, "%s %s %d %d", str, str, &n, &m);
    Edge** edges = new Edge*[m];
    for (int i = 0; i < m; ++i) {
        int u, v;
        fscanf(fin, "%s %d %d", str, &u, &v);
        --u; --v;
        edges[i] = new Edge(u, v);
    }
    ElementSet* nodes = new ElementSet(n);
    EdgeSet* edgeSet = new EdgeSet(m, edges);

    ElementSet* result = generalGraphCanonization(nodes, edgeSet);

    fclose(fin);
    delete result;
    delete nodes;
    delete edgeSet;
    return 0;
}
