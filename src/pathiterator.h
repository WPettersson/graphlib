#ifndef PATHITERATOR_H
#define PATHITERATOR_H

#include <vector>

class Edge;
class Graph;

class PathIterator
{
  public:
    PathIterator(const Graph *g, int now, int target, int length, 
        bool avoid[], int smallest = 0, int avoidColour = 0);
    bool hasNext();
    std::vector<Edge *> next();

    ~PathIterator();

  private:
    bool findNext();

    bool validNextVert(int v) const;

    const Graph *graph;

    int length;
    int nowVert;
    int targetVert;
    int smallest;
    bool *avoid;
    unsigned int nextEdgeIndex;
    int nextVert;
    Edge *nextEdge;
    bool last;

    bool toFind;
    bool found;

    PathIterator *nextPaths;
    std::vector<Edge *> nextPath;

    bool doneClose;
    int avoidColour;

};

#endif /* PATHITERATOR_H */
