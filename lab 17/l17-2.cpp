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
  Program qp(CGAL::SMALLER, false, 0, false, 0);
  // setup the QP
  // remember to specify 2D instead of just D
  // it also only expects the upper triangular part of D to be specified (since
  // it's symmetric)
  // --- Your code here
  qp.set_d(0, 0, 2);
  qp.set_d(1, 0, 0); qp.set_d(1, 1, 2);
  qp.set_d(2, 0, -2);qp.set_d(2, 1, 0); qp.set_d(2, 2, 2);
  qp.set_d(3, 0, 0); qp.set_d(3, 1, -2);qp.set_d(3, 2, 0);qp.set_d(3, 3, 2);
  qp.set_a(0, 0, 1); qp.set_a(1, 0, 1); qp.set_b(0, -4);
  qp.set_a(0, 1, -0.5); qp.set_a(1, 1, 0); qp.set_b(1, 2);
  qp.set_a(0, 2, 0.1); qp.set_a(1, 2, -0.4); qp.set_b(2, 1);
  // qp.set_a(2, 3, -1); qp.set_a(3, 3, -1.6); qp.set_b(3, 1);
  qp.set_a(2, 4, -1); qp.set_a(3, 4, 0); qp.set_b(4, 1);
  qp.set_a(2, 5, 1); qp.set_a(3, 5, 1.5); qp.set_b(5, 2);
  qp.set_a(2, 6, 0.1); qp.set_a(3, 6, -0.4); qp.set_b(6, 1);
  const int n = 4;
  // ---
  Solution s = CGAL::solve_quadratic_program(qp, ET{});
  double optimal_value = CGAL::to_double(s.objective_value());
  auto it = s.variable_values_begin();
  Eigen::Matrix<double, n, 1> x;
  x << CGAL::to_double(*it), CGAL::to_double(*(++it)), CGAL::to_double(*(++it)),
      CGAL::to_double(*(++it));
  std::cout << s;
  std::cout << "optimal value: " << optimal_value << std::endl;
  std::cout << x << std::endl;
}