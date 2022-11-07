#include <CGAL/MP_Float.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
#include <CGAL/Quotient.h>
#include <math.h>

#include <eigen3/Eigen/Eigen>

typedef CGAL::MP_Float ET;
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

Program setup_lp(std::istream& input) {
  // --- Your code here
  Program qp(CGAL::LARGER, true, 0, false, 0);
  Eigen::VectorXd c(4);
  c << 75, 128, 70, 34;
  Eigen::MatrixXd A(4, 5);
  A << 1.6, 3.5, 0.1, 2.3, 6.1, 7.2, 2.1, 7.1, 3.2, 0.1, 3.7, 3.2, 2.9, 3.4,
      4.9, 0.1, 0.15, 0.1, 0.15, 0.1;
  for (int i = 0; i < 4; i++) {
    qp.set_c(i, c(i));
  }
  qp.set_c0(0);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      qp.set_a(i, j, A(i, j));
    }
  }
  double requirement;
  for (int i = 0; i < 5; i++) {
    input >> requirement;
    qp.set_b(i, requirement);
  }
  return qp;
  // ---
}