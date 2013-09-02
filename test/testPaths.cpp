#include <iostream>
#include <array>


#include "graph.h"
#include "edge.h"

int main(int argc, char** argv)
{
  Graph g(5);
  g.addEdge(0,1);
  g.addEdge(0,2);
  g.addEdge(0,3);
  g.addEdge(1,2);
  g.addEdge(1,3);
  g.addEdge(1,4);
  g.addEdge(2,3);
  g.addEdge(2,4);
  g.addEdge(3,4);

  //std::array<bool, 5> avoid; TODO c++14 std?
  //avoid.fill(false);

  bool* avoid = new bool[5];
  for (int i = 0; i < 5; i++)
  {
    avoid[i]=false;
  }
  PathIterator p(&g,0,4,4,avoid,0);
  while (p.hasNext())
  {
    std::cout << "New path" << std::endl;
    for (auto & e: p.next() )
      std::cout << e->toString() << " ";
    std::cout << std::endl;
  }
}


