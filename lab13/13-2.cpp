#include <eigen3/Eigen/Eigen>
#include <iostream>
int main() {
  Eigen::Matrix<double, 12, 3> points;
  points << 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 1, 1, 0, 1, 2, 0, 2, 0, 0, 2, 1,
      0, 2, 2, 0, 3, 0, 0, 3, 1, 0, 3, 2, 0;
  // create the A matrix from points
  Eigen::MatrixXd A(12, 3);
  A.col(0) = points.col(0);
  A.col(1) = points.col(1);
  A.col(2) = Eigen::VectorXd::Ones(12);
  // create the b matrix from points
  Eigen::VectorXd b = points.col(2);
  // solve for x
  Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
  // convert x to our plane coefficients
  std::cout << x;
  return 0;
}