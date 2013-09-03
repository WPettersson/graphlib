#include "pathiterator.h"
#include "graph.h"

#include <iostream>

PathIterator::PathIterator(const Graph *g, int now, int target, int length, 
    bool *avoid, int smallest) : graph(g), length(length), nowVert(now),
    targetVert(target), smallest(smallest), avoid(avoid), nextEdgeIndex(0),
    last(false), toFind(true), nextPaths(NULL), doneClose(false)
{
  this->avoid[nowVert] = true;

//  std::cout << "Finding path from " << nowVert << " to " << targetVert << " with length " << length << std::endl;
//  std::cout << "Smallest " << smallest << std::endl;
//  for (int i = 0; i < 23; i++)
//    if (avoid[i])
//      std::cout << i << " ";
//  std::cout << std::endl;
//  std::cout << graph->toString();
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
  if ((length == 1) || (length == 0 && doneClose == false))
  {
    Edge *e = graph->getEdge(nowVert, targetVert);
    if (e != NULL && e->colour == 0)
    {
      if (length == 1)
        last = true;
      if (length == 0)
        doneClose = true;
      nextPath.clear();
      nextPath.push_back(e);
      return true;
    }
  }
  if (length != 1)
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
      if (!validNextVert(nextVert) || (nextVert == targetVert))
        continue;
      int nextLength = (length==0) ? 0 : length-1;
      nextPaths = new PathIterator(graph, nextVert, targetVert, nextLength, avoid,
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
  }
  last = true;
  return false;
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
