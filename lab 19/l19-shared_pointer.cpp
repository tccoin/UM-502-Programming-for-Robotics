#include <iostream>
#include <memory>

using namespace std;

struct Circle {
  double cx;
  double cy;
  double r;
  Circle(double cx_, double cy_, double r_) : cx(cx_), cy(cy_), r(r_) {}
};

int main() {
  auto circle = make_shared<Circle>(0.1, 0.4, 0.5);
  std::shared_ptr<Circle> circle1(new Circle(0.1, 0.4, 0.5));
  //   auto circle = new Circle(0.1, 0.4, 0.5);
  std::shared_ptr<Circle> circle2 = std::make_shared<Circle>(0.1, 0.4, 0.5);
  //  std::shared_ptr<Circle> circle(0.1, 0.4, 0.5);
  //   std::shared_ptr<Circle> circle3 = new Circle(0.1, 0.4, 0.5);
  //   std::shared_ptr<Circle> circle = auto(0.1, 0.4, 0.5);
  return 0;
}