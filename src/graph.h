#ifndef GRAPH_H
#define GRAPH_H

#include <string>

#include "pathiterator.h"
#include "edge.h"


class Graph
{
  public:
    Graph(int nVerts);
    Edge *getEdge(int, int) const;
    void addEdge(int, int);

  private:
    bool rampingUp;
    int rampTo[];
    int checkpoint[];
   
    int nVerts;

    // C++ doesn't support variable length multidimensional arrays
    // C++14 standard introduces std::array, but for now we use this mess.
    Edge*** edgeLists;
    bool done;
    //std::vector<Step *> steps;

    friend class PathIterator;
};

#endif /* GRAPH_H */
