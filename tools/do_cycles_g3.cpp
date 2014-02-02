#include <sstream>
#include <iostream>

#include "graph.h"
#include "edge.h"
#include "cyclefill.h"

int result;
const int SECONDS_IN_MINUTE = 60;

void callback(Graph *g)
{
  g->writeAsy();
  g->writeTxt();
  g->finish();
  result = 0;
}

int main(int argc, char** argv)
{
  std::vector<int> cycles;
  result = 1;
  int threes = atoi(argv[1]);
  unsigned int n = 3*threes;
  // Skip name of program and no. of 3-cycles
  for (int i = 2; i < argc; i++)
  {
    int len = atoi(argv[i]);
    cycles.push_back(len);
    n += len;
  }
  std::stringstream stream;
  stream << "J" << n << "-into-";
  for (int c:cycles)
    stream << c << ",";
  for (int i=0; i < threes; i++)
    stream << "3,";
  std::string name = stream.str();
  if (name[name.length()-1] == ',')
    name.pop_back();

  std::cout << "Doing " << name << std::endl;
  int nVerts = n+7;
  Graph g(nVerts, name);
  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdgeRange(5,n-1,1);
  g.addEdge(n+3,n+4);
  g.addEdge(n+4,n+5);

  g.addEdge(2,4);
  g.addEdgeRange(4,n+1,2);
  g.addEdge(n+3,n+5);

  g.addEdgeRange(3,n+2,3);

  g.addEdge(0,4);
  g.addEdge(1,5);
  g.addEdgeRange(3,n-1,4);
  g.addEdge(n+2,n+6);

  g.addEdgeRange(1,n,5);

  g.addEdgeRange(0,n-1,6);

  g.addEdgeRange(0,n-1,7);

  //std::array<bool, 5> avoid; TODO c++14 std?
  //avoid.fill(false);

  unsigned int avoid[7][7] = { {n,n+1,n+2,3,n+4,5,n+6},
                    {0,n+1,n+2,n+3,4,5,n+6},
                    {0,n+1,2,3,n+4,n+5,n+6},
                    {0,1,n+2,n+3,4,n+5,n+6},
                    {0,1,2,3,4,n+5,6},
                    {n,1,2,3,n+4,n+5,n+6},
                    {0,1,2,n+3,n+4,5,n+6}};

  if (g.twoFactorTriangle(0,false,avoid))
    callback(&g);
  return result;
}


