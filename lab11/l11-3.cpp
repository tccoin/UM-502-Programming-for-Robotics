#include <cmath>  // can find math constants here, like for pi
#include <iomanip>
#include <iostream>
#include <string>
class Shape2D {
 public:
  Shape2D() {}
  //   virtual double area() const { return 0; }
  virtual double area() const = 0;
  const std::string& getType() const { return type; }
  void setType(const std::string& type) { this->type = type; }

 private:
  std::string type;
};

class Circle : public Shape2D {
  double r;

 public:
  Circle(double r_) : r(r_) {}
  virtual double area() const { return 3.14 * r * r; }
  void scale(double a) { r *= a; }
};

class Triangle : public Shape2D {
  double b, h;

 public:
  Triangle(double b_, double h_) : b(b_), h(h_) {}
  virtual double area() const { return 0.5 * b * h; }
  void setBase(double b_) { b = b_; }
  void setHeight(double h_) { h = h_; }
};

template <class T, class S>
bool operator<(T& a, S& b) {
  return a.area() < b.area();
}

// bool operator<(const Shape2D& a, const Shape2D& b) {
//   return a.area() < b.area();
// }

class PositionedShape {
  const Shape2D& shape;
  double _x, _y;
  double _cachedArea;

 public:
  PositionedShape(double x, double y, const Shape2D& s)
      : shape(s), _x(x), _y(y) {
    _cachedArea = shape.area();
  }
  double area() const { return _cachedArea; }
};

int main() {
  // Shape2D s0;

  Circle c1{2};
  Triangle t1{3, 4};
  PositionedShape ps1(0, 1, t1);

  Shape2D& s1 = c1;
  Shape2D& s2 = t1;

  std::cout << "c1.area: " << c1.area() << std::endl;
  std::cout << "t1.area: " << t1.area() << std::endl;
  std::cout << "ps1.area: " << ps1.area() << std::endl;

  std::cout << "s1.area: " << s1.area() << std::endl;
  std::cout << "s2.area: " << s2.area() << std::endl;

  std::cout << "c1 < t1: " << (c1 < t1) << std::endl;
  std::cout << "t1 < c1: " << (t1 < c1) << std::endl;

  std::cout << "s1 < s2: " << (s1 < s2) << std::endl;
  std::cout << "s2 < s1: " << (s2 < s1) << std::endl;
}