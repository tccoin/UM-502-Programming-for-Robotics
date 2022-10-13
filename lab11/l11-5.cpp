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
  //   double area() const { return 0; }
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
  double area() const { return 3.14 * r * r; }
  void scale(double a) { r *= a; }
};

int main() {
  cout << sizeof(Circle) << endl;
  cout << sizeof(Shape2D) << endl;
}