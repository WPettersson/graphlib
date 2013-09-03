#include "edge.h"

#include <sstream>

Edge::Edge(int v0, int v1)
{
  if (v0 < v1)
  {
    this->v[0] = v0;
    this->v[1] = v1;
  }
  else
  {
    this->v[0] = v1;
    this->v[1] = v0;
  }
  this->colour = 0;
}

bool Edge::touches(int vert) const
{
  if (vert == v[0])
    return true;
  if (vert == v[1])
    return true;
  return false;
}

int Edge::other(int vert) const
{
  if (vert == v[0])
    return v[1];
  return v[0];
}

int Edge::length() const
{
  return v[1] - v[0];
}

std::string Edge::toString() const
{
  std::ostringstream s;
  s << "{" << this->v[0] << "," << this->v[1] << "}";
  std::string str = s.str();
  return str;
}
