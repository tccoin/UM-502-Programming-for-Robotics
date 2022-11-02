#include <math.h>

#include <eigen3/Eigen/Eigen>
#include <iostream>
template <typename Function>
Eigen::VectorXd calculateGradient(Function f, Eigen::VectorXd x, double h) {
  // assumes f is a scalar function with vector input
  // thus gradient has the same dimension as the input (each is just the
  // partial)
  // --- Your code here
  Eigen::Vector2d xi, gradient;
  for (int i = 0; i < x.rows(); i++) {
    xi = x;
    xi(i) += h;
    gradient(i) = (f(xi) - f(x)) / h;
  }
  return gradient;
  // ---
}
double sampleQuadratic(Eigen::Vector2d xy) {
  // x^2 + y^2 = [x y] [1 0; 0 1] [x y]^T
  return xy(0) * xy(0) + xy(1) * xy(1);
}
int main() {
  Eigen::Vector2d x;
  x << 0.5, 0.8;
  auto h = 0.001;
  auto d = calculateGradient(sampleQuadratic, x, h);
  std::cout << d << std::endl;
}