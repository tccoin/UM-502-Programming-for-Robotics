#include <math.h>

#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

Eigen::Matrix3d make_transform_mat(double theta, double dx, double dy) {
  Matrix3d T;
  T << cos(theta), -1 * sin(theta), dx, sin(theta), cos(theta), dy, 0, 0, 1;
  return T;
};

void calc(double theta, double dx, double dy, double x, double y) {
  Vector3d p(x, y, 1);
  cout << (make_transform_mat(theta, dx, dy) * p).head(2) << endl << endl;
}

int main() {
  calc(0, 1, 0, 0, 0);
  calc(1.5707, 0, 0, 0, 1);
  calc(-1.5707, 1, -1, 0, 0);
  calc(-2, 0.56, 0.11, -1, 0.5);
  calc(2, 0, -0.3, 1, 0.2);
  calc(3, 0.5, 0.5, 0.5, 0.5);
  return 0;
}