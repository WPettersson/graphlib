#include "graph.h"
#include "edge.h"

Graph::Graph(int nVerts)
{
  this->nVerts = nVerts;
  this->edgeLists = new Edge**[nVerts];
  for (int i = 0; i < nVerts; i++) 
  {
    this->edgeLists[i] = new Edge*[nVerts];
    for (int j = 0; j < nVerts; j++) {
      this->edgeLists[i][j] = NULL;
    }
  }
}


void Graph::addEdge(int v1, int v2)
{
  Edge* e = new Edge(v1,v2);
  this->edgeLists[v1][v2] = e;
  this->edgeLists[v2][v1] = e;
}

Edge* Graph::getEdge(int v1, int v2) const
{
  return this->edgeLists[v1][v2];
}
