#include "BoundedValenceGraphCanonization.h"

#include "BipartiteGraphCanonization.h"
#include "GraphCanonization.h"

#include <vector>

using namespace std;

PermutationGroupCoset* boundedValenceGraphCanonization(
    ElementSet* nodes, 
    EdgeSet* edgeSet
) {
    int n = nodes->getN();
    int m = edgeSet->getN();
    if (m == 0) {
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
    vector< vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        adj[edges[i]->getFrom()].push_back(i);
        adj[edges[i]->getDest()].push_back(i);
    }
    vector<int> curQueue;
    vector<int> nextQueue;
    curQueue.push_back(edges[0]->getFrom());
    curQueue.push_back(edges[0]->getDest());
    for (int i = 0; i < n; ++i) markNode[i] = false;
    markNode[edges[0]->getFrom()] = true;
    markNode[edges[0]->getDest()] = true;
    for (int i = 0; i < m; ++i) markEdge[i] = false;
    markEdge[0] = true;
    int cnt = m - 1;
    int* permArray1 = new int[n];
    int* permArray2 = new int[n];
    for (int i = 0; i < n; ++i) permArray1[i] = i;
    permArray1[edges[0]->getFrom()] = edges[0]->getDest();
    permArray1[edges[0]->getDest()] = edges[0]->getFrom();
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
    curNodes.push_back(edges[0]->getFrom());
    curNodes.push_back(edges[0]->getDest());
    curEdges.push_back(edges[0]);
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

        int* tmpNodes = new int[curNodes.size()];
        for (int i = 0; i < (int)curNodes.size(); ++i)
            tmpNodes[i] = curNodes[i];
        Edge** tmpEdges = new Edge*[curEdges.size()];
        for (int i = 0; i < (int)curEdges.size(); ++i)
            tmpEdges[i] = curEdges[i];
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
                    curEdges.push_back(edges[edgeIdx]);
                    --cnt;
                }
            }
        }

        int* tmpRightNodes = new int[nextQueue.size()];
        for (int i = 0; i < (int)nextQueue.size(); ++i)
            tmpRightNodes[i] = nextQueue[i];
        tmpEdges = new Edge*[curEdges.size()];
        for (int i = 0; i < (int)curEdges.size(); ++i)
            tmpEdges[i] = curEdges[i];
        ElementSet* tmpRightNodesSet = 
            new ElementSet(nextQueue.size(), tmpRightNodes);
        tmpEdgeSet = new EdgeSet(curEdges.size(), tmpEdges);

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
    delete[] permArray1;
    delete[] permArray2;
    return result;
}
