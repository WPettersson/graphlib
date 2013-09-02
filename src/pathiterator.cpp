#include "pathiterator.h"
#include "graph.h"

PathIterator::PathIterator(const Graph *g, int now, int target, int length, 
    bool *avoid, int smallest = 0)
{
  this->graph = g;
  this->length = length;
  // Check for valid length (>0).
  if (length == 0)
    this->last = true;
  else
    this->last = false;
  this->nowVert = now;
  this->targetVert = target;
  this->nextEdgeIndex = 0;
  this->avoid = avoid;
  this->avoid[nowVert] = true;
  this->smallest = smallest;
  this->nextPaths = NULL;

  this->toFind = true;
}

PathIterator::~PathIterator()
{
  this->avoid[nowVert] = false;
}

bool PathIterator::validNextVert(int v) const
{
  if (avoid[v])
    return false;
  if (v < smallest)
    return false;
  if (v == targetVert)
    return false;
  return true;
}

bool PathIterator::findNext()
{
  if (last)
    return false;
  else if (length == 1)
  {
    Edge *e = graph->getEdge(nowVert, targetVert);
    if (e != NULL)
    {
      last = true;
      nextPath.clear();
      nextPath.push_back(e);
      return true;
    }
    return false;
  }
  else
  {
    if (nextPaths)
    {
      if (nextPaths->hasNext()) 
      {
        nextPath = nextPaths->next();
        nextPath.push_back(nextEdge);
        return true;
      }
      else
      {
        delete nextPaths;
        nextPaths = NULL;
      }
    }
    while (++nextEdgeIndex < graph->nVerts)
    {
      nextEdge = graph->edgeLists[nowVert][nextEdgeIndex];
      if (nextEdge == NULL)
        continue;
      if (nextEdge->colour != 0) 
        continue;
      nextVert = nextEdge->other(nowVert);
      if (!validNextVert(nextVert))
        continue;
      nextPaths = new PathIterator(graph, nextVert, targetVert, length-1, avoid,
          smallest);
      if (nextPaths->hasNext())
      {
        nextPath = nextPaths->next();
        nextPath.push_back(nextEdge);
        return true;
      }
      else
      {
        delete nextPaths;
        nextPaths = NULL;
      }
    }
    return false;
  }
}

bool PathIterator::hasNext()
{
  if (toFind)
  {
    found = findNext();
    toFind = false;
  }
  return found;
}

std::vector<Edge *> PathIterator::next()
{
  if (toFind)
    findNext();
  toFind = true;
  return nextPath;
}
