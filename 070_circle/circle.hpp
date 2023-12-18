#include <cstdio>
#include <cstdlib>

#include "point.hpp"
class Circle {
 private:
  const double radius;
  Point center;

 public:
  Circle(Point po, double ra) : radius(ra), center(po){};
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
