#include "step.h"

Step::Step()
{
  this.colour = 0;
}

void Step::setColour(int c)
{
  this.colour = c;
}

void Step::avoid(int count, int[] a)
{
  toAvoid(a,a+count);
}
