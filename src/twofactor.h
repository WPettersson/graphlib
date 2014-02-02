#ifndef TWOFACTOR_H
#define TWOFACTOR_H

#include <vector>
class TwoFactor : public Step
{
  public:
    TwoFactor(Graph *g, std::vector<std::vector<int>> avoid, std::vector<int> lengths);
    void run();
  private:
    int *lengths;
    unsigned int count;
    std::vector<bool *> completed;
    unsigned int v;
    int numColours;

    bool firstRun;
    std::vector<std::vector<int>> av;
    std::vector<bool*> avoidArrays;
};
#endif /* TWOFACTOR_H */
