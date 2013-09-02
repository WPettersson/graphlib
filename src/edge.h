#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge
{
  public:
    Edge(int, int);
    bool touches(int) const;
    int other(int) const;
    int colour;

    std::string toString() const;


  private:
    int v[2];
};

#endif /* EDGE_H */
