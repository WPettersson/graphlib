#ifndef STEP_H
#define STEP_H

#include "graph.h"

class Step
{
  public:
    Step();
    virtual void run(Graph) const;
    void setColour(int);
    void avoid(int[]);

  private:
    int colour;
    std::array<int> toAvoid;
}
#endif /* STEP_H */
