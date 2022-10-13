#include <cmath>
#include <eigen3/Eigen/Dense>
#include <fstream>
int main() {
  Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ",
                            "\n");
  std::ofstream outfile{"pendulum_output.csv"};
  if (!outfile.good()) {
    throw std::runtime_error("failed to open file for writing!");
  }
  float const g = 9.8;
  float const l = 0.1;
  float const dt = 0.005;  // this is $\Delta t$
  // Create a vector for [x, xdot] and initialize it to [pi/4, 0]
  // Create the matrix here, it should be 2x2, and should have the values:
  // [ 0 1 ]
  // [ -g/l 0 ]
  // --- Your code here
  Eigen::Vector2d x(M_PI / 4, 0);
  Eigen::Matrix2d A;
  A << 0, 1, -1 * g / l, 0;
  // ---
  // roll out the dynamics using the equation in the lab document
  for (int i{0}; i < 100; ++i) {
    // write the current x to the outfile
    outfile << x.format(CSVFormat) << '\n';
    // now update x based on the dynamics
    // --- Your code here
    x = x + dt * A * x;
    // ---
  }
  // to visualize the output, run `python viz_pendulum.py` using F5 in VSCode.
  return 0;
}