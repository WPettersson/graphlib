#include <sstream>

#include "graph.h"
#include "edge.h"
#include "cycle.h"

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
  int n = 0;
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

  const int avoid[7][7] = { {0,1,n+2,n+3,n+4,n+5,n+6},
                    {0,1,n+2,3,4,n+5,n+6},
                    {0,n+1,2,3,n+4,n+5,n+6},
                    {0,n+1,n+2,n+3,n+4,n+5,6},
                    {n,1,2,3,n+4,5,n+6},
                    {0,1,2,3,n+4,5,6},
                    {n,n+1,2,n+3,4,n+5,n+6}};

  for (int colour = 0; colour < 7; colour++)
  {
    for (auto cycle: cycles)
    {
      std::vector<int> av;
      for (int i = 0; i < 7; i++)
      {
        av.push_back(avoid[colour][i]);
      }
      Step *s = new Cycle(&g, av, cycle, colour+1, 0, false);
      g.addStep(s);
    }
  }
  g.setCallback(&callback);
  g.setCheckpoint(30);
  g.run();
  return result;
}


