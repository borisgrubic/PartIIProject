#include "GraphCanonization.h"

#include <stddef.h>
#include <vector>

using namespace std;

#include "GeneralGraphCanonization.h"
#include "BoundedValenceGraphCanonization.h"
#include "../utils/Utils.h"

ElementSet* generalGraphCanonization(
    ElementSet* nodes,
    EdgeSet* edges
) {
    int n = nodes->getN();
    int m = edges->getN();
    int* colors = new int[n];
    for (int i = 0; i < n; ++i) colors[i] = 0;
    while (naiveRefinement(nodes, edges, colors));
    int* tmpColors = new int[n];
    for (int i = 0; i < n; ++i) tmpColors[i] = colors[i];

    int d = 1;
    while (d * d < n) d++;

    ElementSet* minAdjacencyList = NULL;
    ElementSet* adjacencyList = getAdjacencyList(nodes, edges);
    bool stop = false;
    for (int subsetSize = 0; !stop; ++subsetSize) {
        int* subset = new int[subsetSize];
        for (int i = 0; i < subsetSize; ++i) subset[i] = i;
        do {
            for (int i = 0; i < n; ++i) colors[i] = tmpColors[i];
            for (int i = 0; i < subsetSize; ++i) {
                colors[(*nodes)[subset[i]]] = n + 1;
                while (naiveRefinement(nodes, edges, colors));
            } 

            // update edges
            vector<Edge*> newEdgesVec;
            newEdgesVec.clear();
            bool ok = true;
            for (int i = 0; ok && i < n; ++i) {
                for (int j = 0; ok && j < n; ++j) {
                    if (i == j) continue;
                    int totalColor = 0;
                    for (int k = 0; k < n; ++k)
                        if (colors[k] == colors[j])
                            ++totalColor;
                    bool found = false;
                    int cnt = 0;
                    for (int k = 0; k < m; ++k) {
                        if ((*edges)[k]->getFrom() == (*nodes)[i]) {
                            if ((*edges)[k]->getDest() == (*nodes)[j]) {
                                found = true;
                            }
                            if (colors[nodes->find((*edges)[k]->getDest())] == colors[j]) {
                                ++cnt;
                            }
                        }
                    }
                    if ((found && cnt <= d) || (!found && cnt > d)) {
                        newEdgesVec.push_back(new Edge((*nodes)[i], (*nodes)[j]));
                    }
                    if (cnt > d && cnt < totalColor - d) {
                        ok = false;
                    }
                }
            }

            if (ok) {
                stop = true;
                Edge** edgeArr = new Edge*[newEdgesVec.size()];
                for (int i = 0; i < (int)newEdgesVec.size(); ++i)
                    edgeArr[i] = newEdgesVec[i];
                EdgeSet* edgeSet = new EdgeSet(newEdgesVec.size(), edgeArr);

                ElementSet* tmpAdjacencyList =
                    findMinimalAdjacencyMatrix(
                        nodes,
                        edgeSet,
                        colors
                    );
                delete edgeSet;

                // update minAdjacencyList
                if (minAdjacencyList == NULL || *tmpAdjacencyList < *minAdjacencyList) {
                    if (minAdjacencyList != NULL) {
                        delete minAdjacencyList;
                    }
                    minAdjacencyList = tmpAdjacencyList;
                } else {
                    delete tmpAdjacencyList;
                }
            } else {
                for (int i = 0; i < (int)newEdgesVec.size(); ++i)
                    delete newEdgesVec[i];
            }
        } while (nextSubset(n, subset, subsetSize));
        delete[] subset;
    }

    delete adjacencyList;
    delete[] colors;
    delete[] tmpColors;
    return minAdjacencyList;
}
