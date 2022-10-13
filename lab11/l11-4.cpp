#include <algorithm>
#include <cmath>  // can find math constants here, like for pi
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
  Circle(double r_) : r(r_) { setType("Circle r:" + to_string(r)); }
  virtual double area() const { return 3.14 * r * r; }
  // void scale(double a) { r *= a; }
};

class Triangle : public Shape2D {
  double b, h;

 public:
  Triangle(double b_, double h_) : b(b_), h(h_) {
    setType("Triangle base:" + to_string(b));
  }
  virtual double area() const { return 0.5 * b * h; }
  // void setBase(double b_) { b = b_; }
  // void setHeight(double h_) { h = h_; }
};

// template <class T, class S>
// bool operator<(T& a, S& b) {
//   return a.area() < b.area();
// }

bool compare1(Shape2D* a, Shape2D* b) { return a->area() < b->area(); }
bool compare2(const Shape2D* a, const Shape2D* b) {
  return a->area() < b->area();
}

int main() {
  {
    Circle c1{1.652};
    Circle c2{1.9123};
    Triangle t1{3.72, 5.432};
    Triangle t2{4.12, 4.552};
    Triangle t3{2.623, 6.52};
    std::vector<Shape2D*> shapes{&c1, &c2, &t1, &t2, &t3};
    sort(shapes.begin(), shapes.end(), compare1);
    for (auto& shape : shapes) {
      cout << shape->getType() << ": " << shape->area() << endl;
    }
  }
  {
    const Circle c1{1.652};
    const Circle c2{1.9123};
    const Triangle t1{3.72, 5.432};
    const Triangle t2{4.12, 4.552};
    const Triangle t3{2.623, 6.52};
    std::vector<const Shape2D*> shapes{&c1, &c2, &t1, &t2, &t3};
    sort(shapes.begin(), shapes.end(), compare2);
    for (auto& shape : shapes) {
      cout << shape->getType() << ": " << shape->area() << endl;
    }
  }
}