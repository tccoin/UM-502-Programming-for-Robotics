#include <math.h>

#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main() {
  Vector2i a(0, 1);
  Vector3d b(0.1, -0.1, 3.0);
  Vector4d c(0.2, -0.2, 0.0, 1.0);
  Matrix2i d;
  d << 0, 1, 2, 3;
  Matrix3d e;
  e << cos(M_PI / 2.0), -1 * sin(M_PI / 2.0), 0, sin(M_PI / 2.0),
      cos(M_PI / 2.0), 0, 0, 0, 1;
  MatrixXd f(5, 2);
  f << 0.1, 0.1, 0.2, 0, 0.3, -0.1, 0.4, 0, 0.5, 0.1;
  assert(std::abs(e.sum() - 1) < 0.01);
  assert(std::abs(f.sum() - 1.6) < 0.01);
  Matrix3d g = Matrix3d::Identity();
  Matrix3d h = g + e;
  Matrix2i i = d.transpose();
  Vector3d j = b.cwiseAbs();
  Matrix3d k = h.colwise() + j;
  VectorXd l = f.rowwise().mean();
  Matrix3d m = e * e.transpose();
  Array2i n = a.array() + 5;
  Matrix3d o = k + m;

  cout << m.trace() << endl;
  cout << o(0, 0) << endl;

  Vector3d o_first_row = o.row(0);
  Vector3d f_head = f.col(0).head(3);
  double p = o_first_row.dot(f_head);
  cout << "p: " << p << endl;
  return 0;
}