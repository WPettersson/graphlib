#include <sstream>
#include <iostream>

#include "graph.h"
#include "cyclefill.h"
#include "path.h"

int result;
int count;
const int SECONDS_IN_MINUTE = 60;

void callback(Graph *g)
{
  g->writeAsy();
  g->writeTxt();
  g->finish();
  std::cout << "Found " << count++ << std::endl;
  //std::cin.ignore();
  result = 0;
}

int main(int argc, char** argv)
{
  std::vector<int> cycles;
  // Skip name of program
  result = 1;
  count = 0;
  int pathLen = atoi(argv[1]);
  int n = pathLen;
  for (int i = 2; i < argc; i++)
  {
    int len = atoi(argv[i]);
    cycles.push_back(len);
    n += len;
  }
  std::stringstream stream;
  stream << "M" << n << "-into-P" << pathLen << "+,";
  for (int c:cycles)
    stream << c << ",";
  std::string name = stream.str();
  if (name[name.length()-1] == ',')
    name.pop_back();

  int nVerts = n+7;
  Graph g(nVerts, name);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdge(n+3,n+4);
  g.addEdgeRange(4,n,1);

  g.addEdge(1,3);
  g.addEdgeRange(4,n,2);
  g.addEdge(n+2,n+4);
  g.addEdge(n+3,n+5);

  g.addEdgeRange(3,n+2,3);
  g.addEdgeRange(0,n-1,4);
  g.addEdgeRange(1,n,5);
  g.addEdgeRange(1,n,6);
  g.addEdgeRange(0,n-1,7);

  const int dontTouchSize[] = { 5,5,5,5,5,5,5};
  const int dontTouch[7][6] = { 
    {0,2,3,4,n+6},
    {0,5,n+1,n+3,n+6},
    {4,n+1,n+3,n+5,n+6},
    {0,1,2,n+5,n+6},
    {0,1,3,n+2,n+4},
    {1,2,n+3,n+4,n+6},
    {0,3,n+2,n+4,n+5}};

  const int endPts[][2] = {{1,5},{2,4},{0,2},{3,4},{5,6},{0,5},{1,6}};

  for (int colour = 0; colour < 7; colour++)
  {
    std::vector<int> *av = new std::vector<int>;
    for (int i = 0; i < dontTouchSize[colour]; i++)
    {
      av->push_back(dontTouch[colour][i]);
    }

    std::vector<int> starts;
    std::vector<int> ends;
    for (int i = 0; i < 2; i++)
    {
      starts.push_back(endPts[colour][i]);
      ends.push_back(endPts[colour][i]+n);
    }
    Step *p = new Path(&g, *av, pathLen, starts, ends, colour+1);
    g.addStep(p);
    if (cycles.size() > 0)
    {
      Step *s = new CycleFill(&g, *av, cycles, colour+1);
      g.addStep(s);
    }
  }
  g.setCallback(&callback);
  g.setCheckpoint(30*SECONDS_IN_MINUTE);
  //g.sortSteps();
  g.run();
  return result;
}


