#include <string>

Edge::Edge(int[] v)
{
  this.v[0] = v[0];
  this.v[1] = v[1];
  this.colour = 0;
}

int Edge::touches(int v) const
{
  if (v == v[0])
    return true;
  if (v == v[1])
    return true;
  return false;
}

int Edge::other(int v) const
{
  if (v == v[0])
    return v[1];
  return v[0];
}

std::string Edge::toString() const
{
  std::ostringstream s;
  s << "{" << this.v[0] << "," << this.v[1] << "}";
  std::string str = s.str();
  return str;
}
