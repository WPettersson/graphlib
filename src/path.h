#ifndef PATH_H
#define PATH_H

class Path : public Step
{
  public:
    Path();
    void setLength(int);
    void run(Graph) const;
  private:
    int length;
}
#endif /* PATH_H */
