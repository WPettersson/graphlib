#ifndef PATHITERATOR_H
#define PATHITERATOR_H

#include <vector>

class Edge;
class Graph;

class PathIterator
{
  public:
    PathIterator(const Graph *g, int now, int target, int length, 
        bool avoid[], int smallest);
    bool hasNext();
    std::vector<Edge *> next();

    ~PathIterator();

  private:
    bool findNext();

    bool validNextVert(int v) const;

    bool toFind;
    bool found;
    
    PathIterator *nextPaths;
    std::vector<Edge *> nextPath;
    const Graph *graph;

    int length;
    int nowVert;
    int targetVert;
    int nextVert;
    int nextEdgeIndex;
    Edge *nextEdge;
    int smallest;
    bool last;
    bool *avoid;

};

#endif /* PATHITERATOR_H */
