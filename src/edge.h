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
    int length() const;

    std::string toString() const;

    int v[2];

};

#endif /* EDGE_H */
