#include <sstream>
#include <iostream>

#include "graph.h"
#include "edge.h"
#include "cycle.h"
#include "twofactor.h"

int result;
const int SECONDS_IN_MINUTE = 60;

void callback(Graph *g)
{
  std::cout << "Found one " << std::endl;
  g->writeAsy();
  g->writeTxt();
  g->finish();
  result = 0;
}

int main(int argc, char** argv)
{
  int n = 0;
  std::vector<int> cycles;
  result = 1;
  // Skip name of program
  for (int i = 1; i < argc; i++)
  {
    int len = atoi(argv[i]);
    cycles.push_back(len);
    n += len;
  }
  std::stringstream stream;
  stream << "J" << n << "-into-";
  for (int c:cycles)
    stream << c << ",";
  std::string name = stream.str();
  if (name[name.length()-1] == ',')
    name.pop_back();

  int nVerts = n+7;
  Graph g(nVerts, name);
  g.addEdgeRange(0,n-1,1);

  g.addEdgeRange(4,n+3,2);

  g.addEdge(n,n+3);
  g.addEdge(1,4);
  g.addEdge(n+2,n+5);
  g.addEdge(n+3,n+6);
  g.addEdgeRange(4,n-1,3);

  g.addEdgeRange(0,n-1,4);
  g.addEdge(0,5);
  g.addEdge(n+1,n+6);
  g.addEdgeRange(2,n-1,5);

  g.addEdgeRange(1,n,6);
  g.addEdgeRange(0,n-1,7);

  //std::array<bool, 5> avoid; TODO c++14 std?
  //avoid.fill(false);

  int avoid[7][7] = { {0,1,n+2,n+3,n+4,n+5,n+6},
                    {0,1,n+2,3,4,n+5,n+6},
                    {0,n+1,2,3,n+4,n+5,n+6},
                    {0,n+1,n+2,n+3,n+4,n+5,6},
                    {n,1,2,3,n+4,5,n+6},
                    {0,1,2,3,n+4,5,6},
                    {n,n+1,2,n+3,4,n+5,n+6}};

  std::vector<std::vector<int>> av;
  for(int i=0; i < 7; i++)
  {
    std::vector<int> avo;
    for(int j=0; j < 7; j++)
    {
      avo.push_back(avoid[i][j]);
    }
    av.push_back(avo);
  }
  Step *s = new TwoFactor(&g, av, cycles);
  g.addStep(s);
  g.setCallback(&callback);
  g.setCheckpoint(30);
  std::cout << name <<std::endl;
  g.run();
  return result;
}


