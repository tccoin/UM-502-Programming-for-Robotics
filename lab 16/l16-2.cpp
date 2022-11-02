#include <math.h>

#include <eigen3/Eigen/Eigen>
#include <iostream>
template <typename Function>
Eigen::MatrixXd calculateJacobian(Function f, Eigen::VectorXd x, double h) {
  // assumes f is a vector function with vector input
  // thus Jacobian has the dimension m x n, where f(x) in R^m and x in R^n
  // --- Your code here
  Eigen::MatrixXd J;
  Eigen::VectorXd tmp = f(x);
  Eigen::VectorXd xi;
  J.resize(tmp.rows(), x.rows());
  for (int i = 0; i < x.rows(); i++) {
    xi = x;
    xi(i) += h;
    J.col(i) = (f(xi) - f(x)) / h;
  }
  return J;
  // ---
}
Eigen::VectorXd pendulumDynamics(Eigen::VectorXd x) {
  auto g = 9.81;
  auto l = 0.1;
  // length
  // state space is angle and angular velocity
  Eigen::VectorXd xdot(x.rows());
  // \dot{x_0} = x_1
  xdot(0) = x(1);
  // \dot{x_1} = angular acceleration = - g / l sin(x_0)
  xdot(1) = -g / l * sin(x(0));
  return xdot;
}
int main() {
  Eigen::Vector2d x;
  x << 1.57, 0.;
  auto h = 0.001;
  auto J = calculateJacobian(pendulumDynamics, x, h);
  std::cout << J << std::endl;
}