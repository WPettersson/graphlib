#include "graph.h"
#include "twofactor.h"
#include "edge.h"

#include <vector>
#include <iostream>
TwoFactor::TwoFactor(Graph *g, std::vector<std::vector<int>> avoid,
    std::vector<int> lengths) : Step(g, std::vector<int>()), av(avoid)
{
  this->numColours = avoid.size();
  this->lengths = new int[lengths.size()];
  this->completed = std::vector<bool *>();
  this->count = lengths.size();
  int i = 0;
  for (int len : lengths) {
    this->lengths[i++] = len;
  }
  this->firstRun = true;
  this->v = 0;
  avoidArrays = std::vector<bool*>() ;
  for( int c = 0; c < numColours; c++)
  {
    bool *complete = new bool[count];
    for( unsigned int j=0; j < count; j++)
      complete[j] = false;
    completed.push_back(complete);
    bool *avoidArray = new bool[graph->nVerts];
    for( unsigned int j=0; j < graph->nVerts; j++)
      avoidArray[j] = false;
    for( int j=0; j < 7; j++) // TODO size of overlap?
      avoidArray[av[c][j]] = true;
    avoidArrays.push_back(avoidArray); 
  }
}

void TwoFactor::run()
{

  if (v == graph->nVerts)
  {
    graph->doNextStep();
    return;
  }
  // Find a colour to use on this vertex

  // First note which colours have been used
  bool used[numColours+1];
  for(int j = 1; j <= numColours; j++)
    used[j] = false;
  for(Edge *e: graph->edgeAdjacency[v])
    used[e->colour] = true;

  int c;
  for (c = 1; c <= numColours; c++)
  {
    if (used[c] == false)
    {
      if (avoidArrays[c-1][v] == true)
        continue;
      break;
    }
  }

  if (c == numColours + 1)
  {
    // Move to next vertex
    v+=1;
    run();
    v-=1;
  }
  else
  {
    for (unsigned int i = 0; i < count ; i++)
    {
      if (completed[c-1][i])
        continue;
      if (i > 0 && lengths[i] == lengths[i-1] && !completed[c-1][i-1])
        continue;
      int length = lengths[i];
      for (Edge *e: graph->edgeAdjacency[v])
      {
        if (e->colour != 0)
          continue;
        int otherEnd = e->other(v);
        if (avoidArrays[c-1][otherEnd] || graph->vertColoured(v, c))
        {
          continue;
        }
        PathIterator p(graph, otherEnd,v,length-1,avoidArrays[c-1],v,c);
        while (p.hasNext())
        {
          std::vector<Edge *> path = p.next();
          if (e->length() < path.front()->length())
            continue;
          path.push_back(e);
          graph->colourPath(path, c);
          completed[c-1][i] = true;
          run();
          if (graph->isDone())
            return;
          graph->unColourPath(path);
          completed[c-1][i] = false;
        }
      }
    }
  }
}

