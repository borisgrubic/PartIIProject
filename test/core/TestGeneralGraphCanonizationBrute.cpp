#include "TestGeneralGraphCanonizationBrute.h"

#include "../../src/core/GeneralGraphCanonization.h"
#include "../../src/types/ElementSet.h"
#include "../../src/types/Edge.h"

#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

bool TestGeneralGraphCanonizationBrute::test() {
    srand(time(0));
    bool over = false;
    cout << endl;
    while (!over) {
        int n = rand() % 20 + 5;
        int* f = new int[n];
        ElementSet* nodes = new ElementSet(n);
        vector<pair<int, int>> possedges;
        possedges.clear();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j)
                    possedges.push_back(make_pair(i, j));
        int cnt = rand() % possedges.size();
        Edge** edges = new Edge*[cnt];
        cout << "nodes = " << (n < 10 ? " " : "") << n << " ";
        cout << "edges = " << (cnt < 100 ? cnt < 10 ? "  " : " " : "") << cnt;
        for (int i = 0; i < cnt; ++i) {
            int t = rand() % possedges.size();
            edges[i] = new Edge(possedges[t].first, possedges[t].second);
            possedges.erase(possedges.begin() + t);
        }
        EdgeSet* edgeSet = new EdgeSet(cnt, edges);
        for (int i = 0; i < n; ++i) f[i] = i;
        for (int i = 0; i < n; ++i) {
            int t = rand() % (n - i);
            swap(f[t], f[n - i - 1]);
        }
        Edge** edges2 = new Edge*[cnt];
        for (int i = 0; i < cnt; ++i)
            edges2[i] = 
                new Edge(f[edges[i]->getFrom()], f[edges[i]->getDest()]);

        int start = clock();
        EdgeSet* edgeSet2 = new EdgeSet(cnt, edges2);
        bool ok = true;
        ElementSet* result1 = generalGraphCanonization(nodes, edgeSet);
        ElementSet* result2 = generalGraphCanonization(nodes, edgeSet2);
        ok &= *result1 == *result2;
        delete result1;
        delete result2;
        int end = clock();

        if (ok) cout << "... OK!  Finished in: " << (end - start) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
        else {
            cout << endl;
            cout << "Wrong!" << endl;
            cout << n << endl;
            cout << endl;
            for (int i = 0; i < cnt; ++i)
                cout << edges[i]->getFrom() << " " << edges[i]->getDest() << endl;
            cout << endl;
            for (int i = 0; i < cnt; ++i)
                cout << edges2[i]->getFrom() << " " << edges2[i]->getDest() << endl;
            cout << endl;
            over = true;
        }
        delete edgeSet2;
        delete edgeSet;
        delete[] f;
        delete nodes;
    }

    return false;
}


