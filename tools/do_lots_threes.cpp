#include <sstream>
#include <iostream>

#include "graph.h"
#include "edge.h"
#include "cycle.h"

int result;
int threes;
unsigned int n;
const int SECONDS_IN_MINUTE = 60;

void callback(Graph *g)
{
  std::cout << "Found one " << std::endl;
  unsigned int avoid[7][7] = { {0,1,n+2,n+3,n+4,n+5,n+6},
                    {0,1,n+2,3,4,n+5,n+6},
                    {0,n+1,2,3,n+4,n+5,n+6},
                    {0,n+1,n+2,n+3,n+4,n+5,6},
                    {n,1,2,3,n+4,5,n+6},
                    {0,1,2,3,n+4,5,6},
                    {n,n+1,2,n+3,4,n+5,n+6}};
  if (g->twoFactorTriangle(0,false,avoid))
  {
    g->writeAsy();
    g->writeTxt();
    g->finish();
    result = 0;
  }
}

int main(int argc, char** argv)
{
  std::vector<int> cycles;
  result = 1;
  threes = atoi(argv[1]);
  n = 3 * threes;
  // Skip name of program and number of threes
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
  stream << "3^" << threes;
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

  for (int colour = 0; colour < 7; colour++)
  {
    std::vector<int> av;
    for (int i = 0; i < 7; i++)
    {
      av.push_back(avoid[colour][i]);
    }
    for (int length: cycles)
    {
      Step *s = new Cycle(&g, av, length, colour+1);
      g.addStep(s);
    }
  }
  g.setCallback(&callback);
  g.setCheckpoint(30);
  std::cout << name <<std::endl;
  g.run();
  return result;
}


