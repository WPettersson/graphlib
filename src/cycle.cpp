#include "graph.h"
#include "cycle.h"
#include "edge.h"

#include <iostream>

Cycle::Cycle(Graph *g, std::vector<int> avoid, int length, int colour,
    int start, bool lowest) : Step(g, avoid, colour), length(length),
    start(start), lowest(lowest)
{

}

void Cycle::run()
{
  updateAvoid();
  for (unsigned int v = start; v <= (graph->nVerts-length); v++)
  {
    if (avoid[v])
      continue;
    for (Edge *e: graph->edgeAdjacency[v])
    {
      if (e->colour != 0)
        continue;
      int otherEnd = e->other(v);
      PathIterator p(graph,otherEnd,v,length-1,avoid,v);
      while (p.hasNext())
      {
        std::vector<Edge *> path = p.next();
        if (e->length() < path.front()->length())
          continue;
        path.push_back(e);
        graph->colourPath(path, colour);
        graph->doNextStep();
        if (graph->isDone())
          return;
        graph->unColourPath(path);
      }
    }
    // If we're only looking on the lowest vertex, then this failed.
    if (lowest)
      return;
  }
  clearAvoid();
}

