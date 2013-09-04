#include "graph.h"
#include "path.h"
#include "edge.h"

Path::Path(Graph *g, std::vector<int> avoid, int length, 
    std::vector<int> _starts, std::vector<int> _ends, int colour) : 
    Step(g, avoid, colour), length(length), lengthSoFar(0)
{
  count = _starts.size();
  starts = new int[count];
  startsUsed = new bool[count];
  ends = new int[count];
  endsUsed = new bool[count];
  for (int i = 0; i < count; i++) 
  {
    starts[i] = _starts[i];
    ends[i] = _ends[i];
    startsUsed[i] = false;
    endsUsed[i] = false;
  }
}

void Path::run()
{
  bool avoidAdded[graph->nVerts];
  for (unsigned int j = 0; j < graph->nVerts; j++)
    avoidAdded[j] = false;
  int i = 0;
  while (startsUsed[i]) 
    i++;
  bool last = false; // Last path to search for
  int pathLength = 0;
  if (i == count-1)
  {
    last = true;
    pathLength = length - lengthSoFar;
  }
  int start = starts[i];
  for (int j = 0; j < count; j++)
  {
    if (endsUsed[j])
      continue;
    PathIterator p(graph,ends[j],start,pathLength,avoid);
    while (p.hasNext())
    {
      std::vector<Edge *> path = p.next();
      graph->colourPath(path, colour);
      endsUsed[j] = true;
      startsUsed[i] = true;
      lengthSoFar += path.size();
      
      bool okPath = true;
      for (Edge *e: path)
      {
        for (int k = 0; okPath && k < count; k++)
        {
          if (!startsUsed[k] && e->touches(starts[k]))
          {
            okPath = false;
            break;
          }
          if (!endsUsed[k] && e->touches(ends[k]))
          {
            okPath = false;
            break;
          }
        }
      }
      if (okPath)
      {
        if (last)
          graph->doNextStep();
        else
        {
          // Update avoid
          for (Edge *e: path)
          {
            if (! avoid[e->v[0]])
            {
              avoidAdded[e->v[0]] = true;
              avoid[e->v[0]] = true;
            }
            if (! avoid[e->v[1]])
            {
              avoidAdded[e->v[1]] = true;
              avoid[e->v[1]] = true;
            }
          }
          run();
          for (unsigned int k = 0; k < graph->nVerts; k++)
          {
            if (avoidAdded[k])
            {
              avoid[k] = false;
              avoidAdded[k] = false;
            }
          }
        }
        if (graph->isDone())
          return;
      }
      graph->unColourPath(path);
      endsUsed[j] = false;
      startsUsed[i] = false;
      lengthSoFar -= path.size();
    }
  }
}

