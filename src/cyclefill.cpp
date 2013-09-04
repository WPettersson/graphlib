#include "graph.h"
#include "cyclefill.h"
#include "edge.h"

#include <algorithm>
#include <vector>

CycleFill::CycleFill(Graph *g, std::vector<int> avoid, 
    std::vector<int> lengths, int colour, bool sorted) : Step(g, avoid, colour)
{
  if ( !sorted)
    std::sort(lengths.begin(), lengths.end());
  this->lengths = new int[lengths.size()];
  this->completed = new bool[lengths.size()];
  this->numberDone = 0;
  this->count = lengths.size();
  int i = 0;
  for (int len : lengths) {
    this->completed[i] = false;
    this->lengths[i++] = len;
  }
  this->firstRun = true;
}

void CycleFill::run()
{
  bool avoidAdded[graph->nVerts];
  // Add any vertices that already touch this colour to the avoid array.  We
  // also track which these are so we can undo this later.
  for (unsigned int i = 0; i < graph->nVerts; i++)
  {
    avoidAdded[i] = false;
    if (!avoid[i] && graph->vertColoured(i, colour))
    {
      avoidAdded[i] = true;
      avoid[i] = true;
    }
  }

  // Find vertex that hasn't used this colour yet
  unsigned int v;
  for (v = 0; v < graph->nVerts; v++)
  {
    if (avoid[v])
      continue;
    bool available = false;
    for (Edge *e: graph->edgeAdjacency[v])
    {
      if (e->colour == 0)
      {
        available = true;
        break;
      }
    }
    if (! available)
      continue;
    break;
  }

  if (v == graph->nVerts)
    goto cleanup;

  for (int i = 0; i < count; i++)
  {
    if (completed[i])
      continue;
    if (i > 0 && lengths[i] == lengths[i-1] && !completed[i-1])
      continue;
    int length = lengths[i];
    for (Edge *e: graph->edgeAdjacency[v])
    {
      if (e->colour != 0)
        continue;
      int otherEnd = e->other(v);
      if (avoid[otherEnd] || graph->vertColoured(otherEnd, colour))
        continue;
      PathIterator p(graph,otherEnd,v,length-1,avoid,v);
      while (p.hasNext())
      {
        std::vector<Edge *> path = p.next();
        if (e->length() < path.front()->length())
          continue;
        path.push_back(e);
        graph->colourPath(path, colour);
        completed[i] = true;
        numberDone += 1;
        if (numberDone == count)
          graph->doNextStep();
        else
          run();
        if (graph->isDone())
          return;
        graph->unColourPath(path);
        completed[i] = false;
        numberDone -= 1;
      }
    }
  }

cleanup:
  // Remove the avoid conditions we added earlier.
  for (unsigned int i = 0; i < graph->nVerts; i++)
  {
    if (avoidAdded[i])
    {
      avoid[i] = false;
    }
  }
}

