#ifndef EDGE_H
#define EDGE_H
class Edge
{
  public:
    Edge(int, int);
    bool touches(int) const;
    int other(int) const;
    int colour;


  private:
    int v[2];
};

#endif /* EDGE_H */
