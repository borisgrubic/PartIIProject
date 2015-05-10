#include "nausparse.h"

#include <iostream>
using namespace std;


int main(int argv, char *argc[]) {
    if (argv != 2) {
        return -1;
    }

    DYNALLSTAT(int,lab,lab_sz);
    DYNALLSTAT(int,ptn,ptn_sz);
    DYNALLSTAT(int,orbits,orbits_sz);
    static DEFAULTOPTIONS_SPARSEDIGRAPH(options);
    statsblk stats;
    sparsegraph sg; 

    FILE* fin = fopen(argc[1], "r");
    int n, m;
    char str[10]; char ch;
    fscanf(fin, "%s %s %d %d", str, str, &n, &m);

    /* Initialise sparse graph structure. */
    SG_INIT(sg);

    SG_ALLOC(sg,n,m,"malloc");
    DYNALLOC1(int,lab,lab_sz,n,"malloc");
    DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
    DYNALLOC1(int,orbits,orbits_sz,n,"malloc");
    sg.nv = n; /* Number of vertices */
    sg.nde = m; /* Number of directed edges */
    int u, v;
    fscanf(fin, "%s %d %d", &str, &u, &v);
    --u; --v;
    int p = 0;
    for (int i = 0; i < n; ++i) {
        sg.d[i] = 0;
        sg.v[i] = p;
        while (p < m && i == u) {
            sg.d[i]++;
            sg.e[p++] = v; 
            if (p < m) {
                fscanf(fin, "%s %d %d", &str, &u, &v);
                --u; --v;
            }
        }
    }

    sparsenauty(&sg,lab,ptn,orbits,&options,&stats,NULL);

    fclose(fin);
    return 0;
}
