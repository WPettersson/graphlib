#include "step.h"
#include "edge.h"
#include "graph.h"

Step::Step(Graph *g, std::vector<int> _avoid, int colour) : graph(g), colour(colour)
{
  this->avoid = new bool[graph->nVerts];
  for (unsigned int i = 0; i < graph->nVerts; i++)
    avoid[i] = false;

  for (int a: _avoid)
    avoid[a] = true;

  for (Edge *e: g->allEdges)
  {
    if (e->colour == colour)
    {
      if (!avoid[e->v[1]])
      {
        avoidedNow.push_back(e->v[1]);
        avoid[e->v[1]] = true;
      }
      if (!avoid[e->v[2]])
      {
        avoidedNow.push_back(e->v[2]);
        avoid[e->v[2]] = true;
      }
    }
  }
}

Step::~Step()
{
  for (int v: avoidedNow)
    avoid[v] = false;
}

void Step::setColour(int c)
{
  this->colour = c;
}

