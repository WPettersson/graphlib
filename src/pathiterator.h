#ifndef PATHITERATOR_H
#define PATHITERATOR_H

class Edge;
class Graph;

class PathIterator
{
  public:
    PathIterator(Graph, int);
    bool hasNext() const;
    std::vector<Edge *> next();

  private:
    void findNext();

    Graph graph;
    int length;
    int nextVertIndex;
}

#endif /* PATHITERATOR_H */
