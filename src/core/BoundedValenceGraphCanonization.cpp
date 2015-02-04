#include "BoundedValenceGraphCanonization.h"

#include "BipartiteGraphCanonization.h"
#include "GraphCanonization.h"

#include <vector>
#include <algorithm>

using namespace std;

PermutationGroupCoset* boundedValenceGraphCanonization(
    ElementSet* nodes, 
    EdgeSet* edgeSet,
    int fixEdgeIdx
) {
    int n = nodes->getN();
    int m = edgeSet->getN();
    if (m == 0) {
        // TODO: fix
        return new PermutationGroupCoset(
            new Permutation(n),
            new PermutationGroup(
                1,
                new Permutation*[1]{
                    new Permutation(n)
                }
            )
        );
    }
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
    vector<int> curQueue;
    vector<int> nextQueue;
    curQueue.push_back(edges[fixEdgeIdx]->getFrom());
    curQueue.push_back(edges[fixEdgeIdx]->getDest());
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
    curNodes.push_back(edges[fixEdgeIdx]->getDest());
    curEdges.push_back(edges[fixEdgeIdx]);
    bool over = false;
    do {
        if (cnt == 0) over = true;
        for (int i = 0; i < (int)curQueue.size(); ++i) {
            int node = curQueue[i];
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
        for (int i = 0; i < (int)curQueue.size(); ++i) {
            int node = curQueue[i];
            for (int j = 0; j < (int)adj[node].size(); ++j) {
                int edgeIdx = adj[node][j];
                int nnode = 
                    edges[edgeIdx]->getFrom() + 
                    edges[edgeIdx]->getDest() -
                    node;
                if (!markNode[nnode]) {
                    markNode[nnode] = true;
                    markEdge[edgeIdx] = true;
                    nextQueue.push_back(nnode);
                    nextEdges.push_back(edges[edgeIdx]);
                    curEdges.push_back(edges[edgeIdx]);
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

        curQueue.clear();
        for (int i = 0; i < (int)nextQueue.size(); ++i) { 
            curQueue.push_back(nextQueue[i]);
            curNodes.push_back(nextQueue[i]);
        }
    } while (!over);

    delete[] markNode;
    delete[] markEdge;
    return result;
}
