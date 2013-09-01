#ifndef CYCLEFILL_H
#define CYCLEFILL_H

class CycleFill : public Step
{
  public:
    CycleFill();
    void setLengths(int []);
    void run(Graph) const;
  private:
    std::vector<int> lengths;
}
#endif /* CYCLEFILL_H */
