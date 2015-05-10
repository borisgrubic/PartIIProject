#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

unsigned short read_word(FILE* in) {
    unsigned char b1, b2;

    b1 = getc(in);
    b2 = getc(in);

    return b1 | (b2 << 8);
}

void read_graph(FILE* in, FILE* out, bool directed) {
    int n, m;
    vector< vector<int> > g;
    g.clear();
    n = read_word(in);
    for (int i = 0; i < n; ++i) g.push_back(vector<int>());

    m = 0;
    for (int i = 0; i < n; ++i) {
        int tmp; tmp = read_word(in);
        m += tmp;

        for (int j = 0; j < tmp; ++j) {
            int v = read_word(in);
            g[i].push_back(v);
            if (!directed) g[v].push_back(i);
        }
    }

    if (!directed) m *= 2;
    fprintf(out, "p edge %d %d\n", n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            fprintf(out, "e %d %d\n", i+1, g[i][j]+1);
        }
    }
}

int main(int argv, char* argc[]) {
    if (argv != 4) {
        return -1;
    }

    FILE* in = fopen(argc[1], "rb");
    FILE* out = fopen(argc[2], "w");

    read_graph(in, out, argc[3][0] - '0');
    fclose(in);
    fclose(out);

    return 0;
}
