#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <iostream>

#include "graph.h"
#include "edge.h"
#include "cycle.h"

Graph::Graph(int nVerts, std::string name) : nVerts(nVerts), done(false),
    stepCount(0), callback(NULL), checkpointing(false), rampingUp(false),
    name(name)
{
  edgeLists = new Edge**[nVerts];
  for (int i = 0; i < nVerts; i++) 
  {
    edgeAdjacency.push_back(std::vector<Edge *>());
    edgeLists[i] = new Edge*[nVerts];
    for (int j = 0; j < nVerts; j++) {
      edgeLists[i][j] = NULL;
    }
  }
}

void Graph::run()
{
  unsigned int numSteps = steps.size();
  checkpoint = new unsigned long[numSteps];
  rampTo = new unsigned long[numSteps];
  for (unsigned int i = 0; i < numSteps; i++)
    checkpoint[i] = 0;
  loadCheckpoint();
  lastChk = clock();
  doNextStep();
}

void Graph::addEdge(int v1, int v2)
{
  Edge* e = new Edge(v1,v2);
  edgeLists[v1][v2] = e;
  edgeLists[v2][v1] = e;
  edgeAdjacency[v1].push_back(e);
  edgeAdjacency[v2].push_back(e);
  allEdges.push_back(e);
}

void Graph::addEdgeRange(int v1, int v2, int length)
{
  for (int i = v1; i <= v2; i++)
    addEdge(i,i+length);
}

void Graph::colourEdge(int v1, int v2, int colour)
{
  getEdge(v1,v2)->colour = colour;
}

bool Graph::vertColoured(int vert, int colour) const
{
  for (Edge *e: edgeAdjacency[vert])
    if (e->colour == colour)
      return true;
  return false;
}

Edge* Graph::getEdge(int v1, int v2) const
{
  return edgeLists[v1][v2];
}

void Graph::colourPath(std::vector<Edge *> path, int colour)
{
  bool badness = false;
  for (Edge *e: path)
  {
    if (colour != 0 && e->colour != 0)
      badness = true;
    e->colour = colour;
  }
  if (badness)
    std::cout << " !!!!!!  Uh oh" << std::endl;
}

void Graph::setCallback( void (*func)(Graph *))
{
  callback = func;
}

void Graph::doNextStep()
{
  if (isDone())
    return;
  if (stepCount == steps.size())
  {
    if (callback != NULL)
      callback(this);
    return;
  }
  Step *s = steps[stepCount];
  if (checkpointing)
  {
    checkpoint[stepCount]+=1;
    unsigned int i = stepCount;
    while (rampingUp && checkpoint[i] == rampTo[i])
    {
      if (++i == steps.size())
        rampingUp = false;
    }
    if (stepCount+1 < steps.size())
      checkpoint[stepCount+1] = 0;
    if (!rampingUp && (clock() - lastChk > chkTimeInterval))
    {
      lastChk = clock();
      saveCheckpoint();
    }
  }
  if ((!rampingUp) || (rampTo[stepCount] == checkpoint[stepCount]))
  {
    stepCount++;
    s->run();
    stepCount--;
  }
}

void Graph::setCheckpoint(int seconds)
{
  chkTimeInterval = seconds*CLOCKS_PER_SEC;
  checkpointing = true;
}

void Graph::saveCheckpoint()
{
  std::ofstream ofile(name + ".chk");
  if (ofile.is_open())
  {
    for (unsigned int i = 0; i < steps.size(); i++)
      ofile << checkpoint[i] << std::endl;
    ofile.close();
  }
}

void Graph::loadCheckpoint()
{
  std::ifstream ifile(name + ".chk");
  if (! ifile.is_open())
    return;
  char buf[80];
  for (unsigned int i = 0; i < steps.size(); i++)
  {
    ifile.getline(buf,80);
    rampTo[i] = atol(buf);
  }
  rampingUp = true;
  ifile.close();
}

std::string Graph::toString(int start) const
{
  std::stringstream str;
  int maxColour = 0;
  for (Edge *e: allEdges)
  {
    if (e->colour > maxColour)
      maxColour = e->colour;
  }
  for (int i = start; i <= maxColour; i++)
  {
    str << i << " = (";
    bool first = true;
    for (Edge *e: allEdges)
    {
      if (e->colour == i)
      {
        if (! first)
          str << ",";
        first = false;
        str << e->toString();
      }
    }
    str << ")" << std::endl;
  }
  return str.str();
}

void Graph::addStep(Step *s)
{
  steps.push_back(s);
}

void Graph::writeAsy(std::string suffix) const
{
  std::ofstream ofile(name + suffix + ".asy");
  ofile << "import Jn;" << std::endl << "init(" << nVerts << ");" << std::endl;
  for (Edge *e: allEdges)
  {
    ofile << "edge (" << e->v[0] << "," << e->v[1] << ",getPen(" << e->colour << "));" << std::endl;
  }
  ofile << "shipout(bbox(white,Fill));" << std::endl;
  ofile.close();
}

void Graph::writeTxtAll(std::string suffix) const
{
  std::ofstream ofile(name + suffix + ".txt");
  ofile << toString(0); // Also write non-used edges
  ofile.close();
}

bool Graph::twoFactorTriangle(unsigned int i, bool empty, unsigned int avoid[][7])
{
  if (i == nVerts)
    return true;
  std::vector<Edge *> adj = edgeAdjacency[i];
  unsigned int numCols = adj.size()/2;
  numCols = 7;
  bool used[numCols+1];
  for(unsigned int j = 1; j <= numCols; j++)
    used[j]=false;
  for(Edge *e: adj)
    used[e->colour] = true;
  unsigned int col;
  for(col = 1; col <= numCols; col++)
  {
    if (used[col]==false)
    {
      bool badColour = false;
      if (avoid != NULL)
      {
        for (int j=0; j< 7; j++)
        {
          if (avoid[col-1][j] == i)
          {
            badColour = true;
            break;
          }
        }
      }
      if (badColour)
        continue;
      break;
    }
  }
  if (col == numCols+1)
  {
    if (twoFactorTriangle(i+1, empty, avoid))
      return true;
  }
  for (unsigned int start = 0; start <  (adj.size()-1) ; start++)
  {
    Edge *startE = adj[start];
    if (startE->colour != 0)
      continue;
    int A = startE->other(i);
    bool badStart = false;
    for (Edge *e: edgeAdjacency[A])
    {
      if (e->colour == (signed)col)
      {
        badStart = true;
        break;
      }
    }
    if (badStart)
        continue;
    for (unsigned int end = start+1; end < adj.size() ; end++)
    {
      Edge *endE = adj[end];
      if (endE->colour != 0)
        continue;
      int B = endE->other(i);
      bool badEnd = false;
      for (Edge *e: edgeAdjacency[B])
      {
        if (e->colour == (signed)col)
        {
          badEnd = true;
          break;
        }
      }
      if (badEnd)
        continue;
      Edge *third = getEdge(A,B);
      if (third == NULL)
        continue;
      if (third->colour != 0)
        continue;
      int sum = 0;
      signed int C = i;
      signed int maxDist = (nVerts+1)/2;
      signed int snVerts = nVerts;
      if ( (C-A > -maxDist) && (C-A < maxDist) )
        sum+= C-A;
      else if ( (C+snVerts - A > -maxDist) && (C+snVerts - A < maxDist) )
        sum+= C+snVerts-A;
      else if ( (C-snVerts - A > -maxDist) && (C-snVerts - A < maxDist) )
        sum+= C-snVerts-A;

      if ( (B-C > -maxDist) && (B-C < +maxDist) )
        sum+= B-C;
      else if ( (B+snVerts - C > -maxDist) && (B+snVerts - C < maxDist) )
        sum+= B+snVerts-C;
      else if ( (B-snVerts - C > -maxDist) && (B-snVerts - C < maxDist) )
        sum+= B-snVerts-C;

      if ( (A-B > -maxDist) && (A-B < maxDist) )
        sum+= A-B;
      else if ( (A+snVerts - B > -maxDist) && (A+snVerts - B < maxDist) )
        sum+= A+snVerts-B;
      else if ( (A-snVerts - B > -maxDist) && (A-snVerts - B < maxDist) )
        sum+= A-snVerts-B;

      if (sum != 0)
        continue;

      colourEdge(i,A,col);
      colourEdge(i,B,col);
      colourEdge(A,B,col);
      //std::cout << "Did " << i << "," << A << "," << B << " in " << col << std::endl;
      if (twoFactorTriangle(i,empty,avoid))
        return true;
      //std::cout << "Undid " << i << "," << A << "," << B << " in " << col << std::endl;
      colourEdge(i,A,0);
      colourEdge(i,B,0);
      colourEdge(A,B,0);
    }
    if (i == 0 && empty)
      return false; // If we're on the first vertex, every edge must be used in some two-factor, so trying other "starting" vertices is equivalent to changing colours.
  }
  return false;
}






void Graph::writeTxt(std::string suffix) const
{
  std::ofstream ofile(name + suffix + ".txt");
  ofile << toString();
  ofile.close();
}
