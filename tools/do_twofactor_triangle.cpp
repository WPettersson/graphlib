#include <sstream>
#include <csignal>

#include "graph.h"
#include "edge.h"
#include "cycle.h"

int result;
const int SECONDS_IN_MINUTE = 60;

Graph *g;

void callback(Graph *graph)
{
  graph->writeAsy();
  graph->writeTxt();
  graph->finish();
  result = 0;
}

void status(int parameter)
{
  g->writeAsy();
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
  stream << "Circ" << n << "-into-";
  for (int c:cycles)
    stream << c << ",";
  std::string name = stream.str();
  if (name[name.length()-1] == ',')
    name.pop_back();

  int nVerts = n;
  g = new Graph(nVerts, name);
  g->addEdgeRange(0,n-2,1);
  g->addEdge(n-1,0);

  g->addEdgeRange(0,n-3,2);
  g->addEdge(n-2,0);
  g->addEdge(n-1,1);

  g->addEdgeRange(0,n-4,3);
  g->addEdge(n-3,0);
  g->addEdge(n-2,1);
  g->addEdge(n-1,2);

  g->addEdgeRange(0,n-5,4);
  g->addEdge(n-4,0);
  g->addEdge(n-3,1);
  g->addEdge(n-2,2);
  g->addEdge(n-1,3);

  g->addEdgeRange(0,n-6,5);
  g->addEdge(n-5,0);
  g->addEdge(n-4,1);
  g->addEdge(n-3,2);
  g->addEdge(n-2,3);
  g->addEdge(n-1,4);

  g->addEdgeRange(0,n-7,6);
  g->addEdge(n-6,0);
  g->addEdge(n-5,1);
  g->addEdge(n-4,2);
  g->addEdge(n-3,3);
  g->addEdge(n-2,4);
  g->addEdge(n-1,5);
  
  g->addEdgeRange(0,n-8,7);
  g->addEdge(n-7,0);
  g->addEdge(n-6,1);
  g->addEdge(n-5,2);
  g->addEdge(n-4,3);
  g->addEdge(n-3,4);
  g->addEdge(n-2,5);
  g->addEdge(n-1,6);


  void (*prev_fn)(int);
  prev_fn = signal (SIGUSR1, status);
  if (prev_fn==SIG_IGN) signal (SIGUSR1, SIG_IGN);

  if (g->twoFactorTriangle())
  {
    callback(g);
  }
  return result;
}


