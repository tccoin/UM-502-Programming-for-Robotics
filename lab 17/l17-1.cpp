#include <CGAL/MP_Float.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
#include <math.h>

#include <eigen3/Eigen/Eigen>
#include <iostream>
typedef CGAL::MP_Float ET;
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
int main() {
  // using QP
  Program qp(CGAL::SMALLER, false, 0, false, 0);
  Eigen::Matrix<double, 3, 3> A;
  // A << 1, 0.5, -0.5, 0, 1, 2.1, -1, 0.2, -0.7;
  A << 1, 0.5, -0.5, 0, 1, 2.1, 0, 2, 4.2;
  Eigen::Vector3d b;
  b << 0.7, 0.4, -0.6;
  // setup the QP
  // --- Your code here
  Eigen::Matrix3d D = A.transpose() * A;
  Eigen::MatrixXd ct = -2 * b.transpose() * A;
  double c0 = b.transpose() * b;
  qp.set_d(0, 0, 2 * D(0, 0));
  qp.set_d(1, 0, 2 * D(1, 0));
  qp.set_d(1, 1, 2 * D(1, 1));
  qp.set_d(2, 0, 2 * D(2, 0));
  qp.set_d(2, 1, 2 * D(2, 1));
  qp.set_d(2, 2, 2 * D(2, 2));
  qp.set_c(0, ct(0));
  qp.set_c(1, ct(1));
  qp.set_c(2, ct(2));
  qp.set_c0(c0);
  // ---
  Solution s = CGAL::solve_quadratic_program(qp, ET{});
  double optimal_value = CGAL::to_double(s.objective_value());
  auto it = s.variable_values_begin();
  Eigen::Vector3d x;
  x << CGAL::to_double(*it), CGAL::to_double(*(++it)), CGAL::to_double(*(++it));
  std::cout << s;
  std::cout << "optimal value: " << optimal_value << std::endl;
  std::cout << x << std::endl;
}