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
    checkpoint[stepCount+1] = 0;
    if (clock() - lastChk > chkTimeInterval)
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

std::string Graph::toString() const
{
  std::stringstream str;
  int maxColour = 0;
  for (Edge *e: allEdges)
  {
    if (e->colour > maxColour)
      maxColour = e->colour;
  }
  for (int i = 1; i <= maxColour; i++)
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

void Graph::writeAsy() const
{
  std::ofstream ofile(name + ".asy");
  ofile << "import Jn;" << std::endl << "init(" << nVerts << ");" << std::endl;
  for (Edge *e: allEdges)
  {
    ofile << "edge (" << e->v[0] << "," << e->v[1] << ",getPen(" << e->colour << "));" << std::endl;
  }
  ofile << "shipout(bbox(white,Fill));" << std::endl;
  ofile.close();
}

void Graph::writeTxt() const
{
  std::ofstream ofile(name + ".txt");
  ofile << toString();
  ofile.close();
}
