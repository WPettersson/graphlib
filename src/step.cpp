#include "step.h"
#include "edge.h"
#include "graph.h"

Step::Step(Graph *g, std::vector<int> _avoid, int colour) : graph(g), colour(colour)
{
  avoid = new bool[graph->nVerts];
  for (unsigned int i = 0; i < graph->nVerts; i++)
    avoid[i] = false;
  for (int a: _avoid)
    avoid[a] = true;
  updateAvoid();
}

void Step::updateAvoid()
{
  if (colour > 0)
  {
    for (Edge *e: graph->allEdges)
    {
      if (e->colour == colour)
      {
        if (!avoid[e->v[0]])
        {
          avoidedNow.push_back(e->v[0]);
          avoid[e->v[0]] = true;
        }
        if (!avoid[e->v[1]])
        {
          avoidedNow.push_back(e->v[1]);
          avoid[e->v[1]] = true;
        }
      }
    }
  }
}

void Step::clearAvoid()
{
  for (auto a: avoidedNow)
    avoid[a] = false;
}

Step::~Step()
{
  clearAvoid();
}

void Step::setColour(int c)
{
  this->colour = c;
}

