#ifndef EDGE_H
#define EDGE_H

class Edge {
    private:
    int from;
    int dest;

    public:
    Edge(Edge*);
    Edge(int, int);
    int getFrom();
    int getDest();
};

#endif

