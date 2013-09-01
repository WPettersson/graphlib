#ifndef GRAPH_H
#define GRAPH_H

#include <string>

#include "pathiterator.h"


class Graph
{
  public:
    Graph();
    bool areAdjacent(int, int);

  //private:
    bool rampingUp;
    int[] rampTo;
    int[] checkpoint;
    
    std::vector<std::vector<Edge *>> edgeLists;
    bool done;
    std::vector<Step *> steps;

    friend class PathIterator;
}

#endif /* GRAPH_H */
