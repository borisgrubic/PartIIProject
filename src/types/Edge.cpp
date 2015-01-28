#include "Edge.h"

Edge::Edge(Edge* nedge) {
    from = nedge->getFrom();
    dest = nedge->getDest();
}

Edge::Edge(int nfrom, int ndest) {
    from = nfrom;
    dest = ndest;
}

int Edge::getFrom() {
    return from;
}

int Edge::getDest() {
    return dest;
}
