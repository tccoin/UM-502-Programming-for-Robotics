#include "lp.h"

#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
  // get initial conditions and goal from input.txt

  std::ifstream input{"input.txt"};
  std::ofstream output{"output.txt"};
  /*  */
  while (input.peek() != EOF) {
    Program lp = setup_lp(input);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
    assert(s.solves_nonnegative_linear_program(lp));

    output << std::fixed << std::setprecision(2);
    output << CGAL::to_double(s.objective_value()) << ' ';
    Eigen::Vector4d x;
    auto it = s.variable_values_begin();
    for (int i = 0; i < 4; ++i, ++it) {
      x(i) = CGAL::to_double(*it);
      output << x(i) << ' ';
    }
    output << std::endl;
    std::cout << s;
    // for debugging
    // Eigen::Matrix<double, 5, 1> completed = A * x;
    // std::cout << std::endl << completed << std::endl;
  }
}