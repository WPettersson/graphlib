#ifndef CYCLE_H
#define CYCLE_H

class Cycle : public Step
{
  public:
    Cycle();
    void setLength(int);
    void run(Graph) const;
  private:
    int length;
}
#endif /* CYCLE_H */
