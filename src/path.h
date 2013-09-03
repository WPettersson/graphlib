#ifndef PATH_H 
#define PATH_H

class Path : public Step
{
  public:
    Path(Graph *g, std::vector<int> _avoid, int length, std::vector<int> starts,
        std::vector<int> ends, int colour);
    void run();
  private:
    int *starts;
    bool *startsUsed;
    int *ends;
    bool *endsUsed;
    int length;
    int lengthSoFar;
    int count;
};
#endif /* PATH_H */
