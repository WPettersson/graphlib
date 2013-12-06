#ifndef CYCLE_H
#define CYCLE_H

class Cycle : public Step
{
  public:
    Cycle(Graph *g, std::vector<int> avoid, int length, int colour, int
        start=0, bool lowest=false);
    void run();
  private:
    int length;
    int start;
    bool lowest;
};
#endif /* CYCLE_H */
