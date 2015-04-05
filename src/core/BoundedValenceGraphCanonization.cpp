#include "BoundedValenceGraphCanonization.h"

#include "BipartiteGraphCanonization.h"
#include "GraphCanonization.h"
#include "../utils/Utils.h"

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

PermutationGroupCoset* boundedValenceGraphCanonization(
    ElementSet* nodes, 
    EdgeSet* edgeSet,
    int fixEdgeIdx,
    int* colors
) {
    int n = nodes->getN();
    int m = edgeSet->getN();
    if (m == 0) {
        int* perm1Array = new int[n];
        Permutation* perm2 = new Permutation(n);
        for (int i = 0; i < n; ++i) perm1Array[i] = (i + 1) % n;
        int tmp = (*perm2)[0];
        (*perm2)[0] = (*perm2)[1];
        (*perm2)[1] = tmp;
        return new PermutationGroupCoset(
            new Permutation(n),
            new PermutationGroup(
                2,
                new Permutation*[2]{
                    new Permutation(n, perm1Array),
                    perm2
                }
            )
        );
    }
    bool newColors = colors == NULL;
    if (newColors) {
        colors = new int[n];
        for (int i = 0; i < n; ++i)
            colors[i] = 0;
    }
    int maxColor = 0;
    for (int i = 0; i < n; ++i) {
        maxColor = max(maxColor, colors[i]);
    }
    ++maxColor;
    Edge** edges = edgeSet->getEdges();
    bool* markNode = new bool[n];
    bool* markEdge = new bool[m];
    vector<int> curNodes;
    vector<Edge*> curEdges;
    vector<Edge*> nextEdges;
    vector< vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        adj[edges[i]->getFrom()].push_back(i);
        adj[edges[i]->getDest()].push_back(i);
    }
    vector<int> nextQueue;
    for (int i = 0; i < n; ++i) markNode[i] = false;
    markNode[edges[fixEdgeIdx]->getFrom()] = true;
    markNode[edges[fixEdgeIdx]->getDest()] = true;
    for (int i = 0; i < m; ++i) markEdge[i] = false;
    markEdge[fixEdgeIdx] = true;
    int cnt = m - 1;
    int* permArray1 = new int[n];
    for (int i = 0; i < n; ++i) permArray1[i] = i;
    permArray1[edges[fixEdgeIdx]->getFrom()] = edges[fixEdgeIdx]->getDest();
    permArray1[edges[fixEdgeIdx]->getDest()] = edges[fixEdgeIdx]->getFrom();
    PermutationGroupCoset* result = new PermutationGroupCoset(
        new Permutation(n),
        new PermutationGroup(
            2,
            new Permutation*[2]{
                new Permutation(n),
                new Permutation(n, permArray1)
            }
        )
    );
    curNodes.push_back(edges[fixEdgeIdx]->getFrom());
    if (edges[fixEdgeIdx]->getFrom() != edges[fixEdgeIdx]->getDest()) {
        curNodes.push_back(edges[fixEdgeIdx]->getDest());
    }
    curEdges.push_back(edges[fixEdgeIdx]);
    bool over = false;
    int curColor = 0;
    do {
        if (cnt == 0) over = true;
        for (int i = 0; i < (int)curNodes.size(); ++i) {
            int node = curNodes[i];
            for (int j = 0; j < (int)adj[node].size(); ++j) {
                int edgeIdx = adj[node][j];
                int nnode = 
                    edges[edgeIdx]->getFrom() + 
                    edges[edgeIdx]->getDest() -
                    node;
                if (markNode[nnode] && !markEdge[edgeIdx]) {
                    curEdges.push_back(edges[edgeIdx]);
                    markEdge[edgeIdx] = true;
                    --cnt;
                }
            }
        }

        sort(curNodes.begin(), curNodes.end());
        int* tmpNodes = new int[curNodes.size()];
        for (int i = 0; i < (int)curNodes.size(); ++i)
            tmpNodes[i] = curNodes[i];
        Edge** tmpEdges = new Edge*[curEdges.size()];
        for (int i = 0; i < (int)curEdges.size(); ++i)
            tmpEdges[i] = new Edge(curEdges[i]);
        EdgeSet* tmpEdgeSet = new EdgeSet(curEdges.size(), tmpEdges);
        ElementSet* tmpElementSet = new ElementSet(curNodes.size(), tmpNodes);
        PermutationGroupCoset* tmpResult = graphCanonization(
            tmpElementSet,
            tmpEdgeSet,
            result
        );

        delete tmpEdgeSet;
        delete result;
        result = tmpResult;

        nextQueue.clear();
        nextEdges.clear();
        for (int i = 0; i < (int)curNodes.size(); ++i) {
            int node = curNodes[i];
            for (int j = 0; j < (int)adj[node].size(); ++j) {
                int edgeIdx = adj[node][j];
                int nnode = 
                    edges[edgeIdx]->getFrom() + 
                    edges[edgeIdx]->getDest() -
                    node;
                if (colors[nnode] != curColor) continue;
                if (!markNode[nnode]) {
                    markNode[nnode] = true;
                    markEdge[edgeIdx] = true;
                    nextQueue.push_back(nnode);
                    curEdges.push_back(edges[edgeIdx]);
                    nextEdges.push_back(edges[edgeIdx]);
                    --cnt;
                }
            }
        }

        sort(nextQueue.begin(), nextQueue.end());
        int* tmpRightNodes = new int[nextQueue.size()];
        for (int i = 0; i < (int)nextQueue.size(); ++i)
            tmpRightNodes[i] = nextQueue[i];
        tmpEdges = new Edge*[nextEdges.size()];
        for (int i = 0; i < (int)nextEdges.size(); ++i)
            tmpEdges[i] = new Edge(nextEdges[i]);
        ElementSet* tmpRightNodesSet = 
            new ElementSet(nextQueue.size(), tmpRightNodes);
        tmpEdgeSet = new EdgeSet(nextEdges.size(), tmpEdges);

        tmpResult = bipartiteGraphCanonization(
            tmpElementSet,
            tmpRightNodesSet,
            tmpEdgeSet,
            result
        );

        delete tmpRightNodesSet;
        delete result;
        delete tmpElementSet;
        delete tmpEdgeSet;
        result = tmpResult;

        for (int i = 0; i < (int)nextQueue.size(); ++i) { 
            curNodes.push_back(nextQueue[i]);
        }

        ++curColor;
        if (curColor == maxColor) {
            curColor = 0;
        }
    } while (!over);

    delete[] markNode;
    delete[] markEdge;
    if (newColors) {
        delete[] colors;
    }
    return result;
}

bool testIsomorphismBetweenBoundedValenceGraphs(
    ElementSet* nodes1,
    EdgeSet* edges1,
    ElementSet* nodes2,
    EdgeSet* edges2
) {
    ElementSet* result1 = findMinimalAdjacencyMatrix(nodes1, edges1);
    ElementSet* result2 = findMinimalAdjacencyMatrix(nodes2, edges2);
    bool ret = (*result1 == *result2);
    delete result1;
    delete result2;
    return ret;
}

// bool testIsomorphismBetweenBoundedValenceGraphs(
//     ElementSet* nodes1,
//     EdgeSet* edges1,
//     ElementSet* nodes2,
//     EdgeSet* edges2
// ) {
//     int n = nodes1->getN();
//     int m = nodes2->getN();
//     int edges1Cnt = edges1->getN();
//     int edges2Cnt = edges2->getN();
//     ElementSet* nodes = new ElementSet(n + m + 2);
//     Edge** edges = new Edge*[edges1Cnt + edges2Cnt + 4];
//     for (int i = 0; i < edges1Cnt; ++i)
//         edges[i] = new Edge((*edges1)[i]);
//     for (int i = 0; i < edges2Cnt; ++i) {
//         edges[i + edges1Cnt] = 
//             new Edge(
//                 (*edges2)[i]->getFrom() + n,
//                 (*edges2)[i]->getDest() + n
//             );
//     }
//     edges[edges1Cnt + edges2Cnt] = new Edge(n + m, edges[0]->getDest());
//     edges[0]->setDest(n + m);
//     edges[edges1Cnt + edges2Cnt + 1] = new Edge(n + m, n + m + 1);
//     edges[edges1Cnt + edges2Cnt + 2] = new Edge(n + m + 1, n + m);
//     edges[edges1Cnt + edges2Cnt + 3] = new Edge(n + m + 1, 0);
//     EdgeSet* edgeSet = new EdgeSet(edges1Cnt + edges2Cnt + 4, edges);
//     bool same = false;
//     for (int i = 0; !same && i < edges2Cnt; ++i) {
//         edges[edges1Cnt + edges2Cnt + 3]->setDest(
//             edges[edges1Cnt + i]->getDest()
//         );
//         edges[edges1Cnt + i]->setDest(n + m + 1);
// 
//         PermutationGroupCoset* result =
//             boundedValenceGraphCanonization(
//                 nodes,
//                 edgeSet,
//                 edges1Cnt + edges2Cnt + 1
//             );
// 
//         for (int j = 0; j < result->getGroup()->getGenSize(); ++j) {
//             Permutation* perm = result->getGroup()->getGenerators()[j];
//             if ((*perm)[n + m] == n + m + 1 && (*perm)[n + m + 1] == n + m) {
//                 same = true;
//             }
//         }
//         delete result;
// 
//         edges[edges1Cnt + i]->setDest(
//             edges[edges1Cnt + edges2Cnt + 3]->getDest()
//         );
//     }
// 
//     delete edgeSet;
//     delete nodes;
//     return same;
// }

void renumberNodes(
    ElementSet* nodes, 
    EdgeSet* edges, 
    int edgeId, 
    int* colors,
    int* perm
) {
    int n = nodes->getN();
    int m = edges->getN();
    vector<int> visited;
    bool* mark = new bool[n];
    visited.clear();
    for (int i = 0; i < n; ++i) mark[i] = false;
    int from = (*edges)[edgeId]->getFrom();
    int dest = (*edges)[edgeId]->getDest();
    int curId = 0;
    visited.push_back(from);
    mark[nodes->find(from)] = true;
    perm[nodes->find(from)] = curId++;
    if (dest != from) {
        visited.push_back(dest);
        mark[nodes->find(dest)] = true;
        perm[nodes->find(dest)] = curId++;
    }
    int curColor = 0;
    vector<int> nextNodes;
    nextNodes.clear();
    int maxColor = 0;
    if (colors != NULL) {
        for (int i = 0; i < n; ++i)
            maxColor = max(maxColor, colors[i]);
    }
    ++maxColor;
    while ((int)visited.size() < n) {
        for (int i = 0; i < (int)visited.size(); ++i) {
            int curNode = visited[i];
            for (int j = 0; j < m; ++j) {
                int v = (*edges)[j]->getFrom();
                int u = (*edges)[j]->getDest();
                int fv = nodes->find(v);
                int fu = nodes->find(u);
                if (curNode == v && !mark[fu]) {
                    if (colors == NULL || colors[fu] == curColor) {
                        mark[fu] = true;
                        perm[fu] = curId++;
                        nextNodes.push_back(u);
                    }
                }
                if (curNode == u && !mark[fv]) {
                    if (colors == NULL || colors[fv] == curColor) {
                        mark[fv] = true;
                        perm[fv] = curId++;
                        nextNodes.push_back(v);
                    }
                }
            }
        }

        curColor++;
        if (curColor == maxColor) {
            curColor = 0;
        }

        for (int i = 0; i < (int)nextNodes.size(); ++i) {
            visited.push_back(nextNodes[i]);
        }
        nextNodes.clear();
    }

    delete[] mark;
}

ElementSet* findMinimalAdjacencyMatrixConnected(
    ElementSet* nodes,
    EdgeSet* edges,
    int* colors
) {
    int n = nodes->getN();
    int m = edges->getN();
    if (m == 0) {
        return getAdjacencyList(nodes, edges);
    }
    ElementSet* result = NULL;
    Edge** newEdgesArray = new Edge*[m];
    for (int i = 0; i < m; ++i) {
        newEdgesArray[i] = new Edge((*edges)[i]);
    }
    EdgeSet* newEdges = new EdgeSet(m, newEdgesArray);
    int* newColors = new int[n];
    int* permArray = new int[n];
    for (int edgeId = 0; edgeId < m; ++edgeId) {
        renumberNodes(nodes, edges, edgeId, colors, permArray);
        for (int i = 0; i < m; ++i) {
            (*newEdges)[i]->setFrom(permArray[(*edges)[i]->getFrom()]);
            (*newEdges)[i]->setDest(permArray[(*edges)[i]->getDest()]);
        }
        if (colors != NULL) {
            for (int i = 0; i < n; ++i)
                newColors[permArray[i]] = colors[i];
        }

        PermutationGroupCoset* tmpResult =
            boundedValenceGraphCanonization(
                nodes,
                newEdges,
                edgeId,
                colors == NULL ? NULL : newColors
            );

        ElementSet* adjacencyList = getAdjacencyList(nodes, newEdges);
        ElementSet* finalGraph = 
            graphInducedAction(adjacencyList, tmpResult->getPermutation(), nodes); 
        delete adjacencyList;
        if (result == NULL || *finalGraph < *result) {
            if (result != NULL) {
                delete result;
            }
            result = finalGraph;
        } else {
            delete finalGraph;
        }
        delete tmpResult;
    }

    delete[] newColors;
    delete[] permArray;
    delete newEdges;
    return result;
}

ElementSet* findMinimalAdjacencyMatrix(
    ElementSet* nodes,
    EdgeSet* edges,
    int* colors
) {
    int n = nodes->getN();
    int m = edges->getN();
    int* mark = new int[n];
    for (int i = 0; i < n; ++i) mark[i] = -1;

    vector<ElementSet*> componentAdjacencyMatrix;
    componentAdjacencyMatrix.clear();

    int* mapTo = new int[n];
    for (int nodeId = 0; nodeId < n; ++nodeId) {
        if (mark[nodeId] != -1) continue;
        int node = (*nodes)[nodeId];
        vector<int> component;
        component.clear();
        queue<int> q;
        while (!q.empty()) q.pop();
        q.push(node);
        component.push_back(node);
        mark[nodeId] = nodeId;
        int edgeCnt = 0;
        while (!q.empty()) {
            int curNode = q.front(); q.pop();
            for (int j = 0; j < m; ++j) {
                int from = (*edges)[j]->getFrom();
                int dest = (*edges)[j]->getDest();
                int ffrom = nodes->find(from);
                int fdest = nodes->find(dest);
                if (from == curNode) ++edgeCnt;
                if (from == curNode && mark[fdest] == -1) {
                    mark[fdest] = nodeId;
                    component.push_back(dest);
                    q.push(dest);
                }
                if (dest == curNode && mark[ffrom] == -1) {
                    mark[ffrom] = nodeId;
                    component.push_back(from);
                    q.push(from);
                }
            }
        }

        int* compNodes = new int[component.size()];
        int* compColors = NULL;
        if (colors != NULL) {
            compColors = new int[component.size()];
        }
        for (int i = 0; i < (int)component.size(); ++i) {
            mapTo[nodes->find(component[i])] = i;
            compNodes[i] = i;
            if (compColors != NULL) {
                compColors[i] = colors[nodes->find(component[i])];
            }
        }
        ElementSet* compNodesSet = new ElementSet(component.size(), compNodes);
        Edge** compEdges = new Edge*[edgeCnt];
        int p = 0;
        for (int i = 0; i < m; ++i) {
            int from = (*edges)[i]->getFrom();
            int dest = (*edges)[i]->getDest();
            int ffrom = nodes->find(from);
            int fdest = nodes->find(dest);
            if (mark[ffrom] == nodeId) {
                compEdges[p++] = new Edge(mapTo[ffrom], mapTo[fdest]);
            }
        }
        EdgeSet* compEdgesSet = new EdgeSet(edgeCnt, compEdges);

        ElementSet* compAdjacencyMatrix =
            findMinimalAdjacencyMatrixConnected(
                compNodesSet,
                compEdgesSet,
                compColors
            );

        componentAdjacencyMatrix.push_back(compAdjacencyMatrix);

        delete compNodesSet;
        delete compEdgesSet;
        delete[] compColors;
    }

    int num = componentAdjacencyMatrix.size();
    for (int i = 0; i < num; ++i)
        for (int j = i + 1; j < num; ++j) {
            if (*componentAdjacencyMatrix[j] < *componentAdjacencyMatrix[i]) {
                swap(componentAdjacencyMatrix[i], componentAdjacencyMatrix[j]);
            }
        }

    ElementSet* result = new ElementSet(n * n);
    int p = 0;
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < componentAdjacencyMatrix[i]->getN(); ++j)
            (*result)[p++] = (*componentAdjacencyMatrix[i])[j];
    }

    for (int i = 0; i < num; ++i)
        delete componentAdjacencyMatrix[i];

    delete[] mark;
    delete[] mapTo;
    return result;
}
