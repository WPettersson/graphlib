#ifndef CYCLEFILL_H
#define CYCLEFILL_H

class CycleFill : public Step
{
  public:
    CycleFill(Graph *g, std::vector<int> avoid, std::vector<int> lengths,
        int colour, bool sorted=false);
    void run();
  private:
    int *lengths;
    int count;
    bool *completed;
    int numberDone;
    int colour;

    bool firstRun;
};
#endif /* CYCLEFILL_H */
