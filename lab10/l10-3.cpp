#include <cmath>  // can find math constants here, like for pi
#include <iomanip>
#include <iostream>
#include <string>
class Shape2D {
 public:
  Shape2D() {}
  double area() const { return 0; }
  const std::string& getType() const { return type; }
  void setType(const std::string& type) { this->type = type; }

 private:
  std::string type;
};

class Circle : public Shape2D {
  double r;

 public:
  Circle(double r_) : r(r_) {}
  double area() const { return 3.14 * r * r; }
  void scale(double a) { r *= a; }
};

class Triangle : public Shape2D {
  double b, h;

 public:
  Triangle(double b_, double h_) : b(b_), h(h_) {}
  double area() const { return 0.5 * b * h; }
  void setBase(double b_) { b = b_; }
  void setHeight(double h_) { h = h_; }
};

int main() {
  Circle c1{1};
  std::cout << c1.getType() << ' ' << std::setprecision(3) << c1.area()
            << std::endl;
  c1.scale(2);
  std::cout << std::setprecision(3) << c1.area() << std::endl;
  Triangle t1{2, 5};
  std::cout << t1.getType() << ' ' << t1.area() << std::endl;
  t1.setBase(3);
  t1.setHeight(4);
  std::cout << t1.area() << std::endl;

  Circle shape{5};
  const std::string& shapeType = shape.getType();
  shape.setType("changed type");
  std::cout << shapeType << std::endl;
}