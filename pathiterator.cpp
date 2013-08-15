#include "pathiterator.h"
#include "graph.h"


PathIterator::PathIterator(const Graph &g, int v, int l)
{
  this.graph = g;
  this.length = l;
  // Nothing adjacent. Shouldn't be possible, best to check.
  if (graph.edgeLists[v].size() == 0)
    this.length = 0;
  this.nextVert = graph.edgeLists[v][0];


}

bool PathIterator::findNext() const
{
  if (length == 0)
    return false;
  if (length == 1)
    if (graph.areAdjacent(v,nextVert))


