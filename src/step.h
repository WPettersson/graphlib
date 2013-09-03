#ifndef STEP_H
#define STEP_H

#include <list>
#include <vector>

class Graph;

class Step
{
  public:
    Step(Graph *g, std::vector<int> avoid, int colour);
    ~Step();
    virtual void run() = 0;
    void setColour(int);

  protected:
    Graph *graph;
    int colour;
    std::list<int> avoidedNow;
    bool *avoid;
};
#endif /* STEP_H */
