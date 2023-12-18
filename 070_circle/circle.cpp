#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double rsum = this->radius + otherCircle.radius;
  double sr = this->radius < otherCircle.radius ? this->radius : otherCircle.radius;
  double lr = this->radius > otherCircle.radius ? this->radius : otherCircle.radius;
  const double rsub = lr - sr;
  const double cdis = this->center.distanceFrom(otherCircle.center);

  if (cdis >= rsum) {
    return 0.0;
  }
  else if (cdis <= rsub) {
    return M_PI * sr * sr;
  }
  else {
    double ags = std::acos((sr * sr + cdis * cdis - lr * lr) / (2.0 * sr * cdis));
    double agl = std::acos((lr * lr + cdis * cdis - sr * sr) / (2.0 * lr * cdis));
    return ags * sr * sr + agl * lr * lr - sr * cdis * std::sin(ags);
  }
}
