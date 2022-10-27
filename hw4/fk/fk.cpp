#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <iomanip>
#include <iostream>

Eigen::Matrix3d transform_mat(double q, double l) {
  // --- Your code here
  return (Eigen::Matrix3d() << cos(q), -sin(q), cos(q) * l, sin(q), cos(q),
          sin(q) * l, 0, 0, 1)
      .finished();

  // ---
}

int main(int argc, char* argv[]) {
  // by defult, use the file joint_angles.txt, but if you supply a command line
  // argument, use that instead
  std::string input_filename{"joint_angles.txt"};
  if (argc >= 2) {
    input_filename = argv[1];
  }
  std::ifstream ifs(input_filename);

  if (!ifs.good()) {
    std::cerr << "Failed to open file " << input_filename << std::endl;
    return 0;
  }

  double l1{1.0};
  double l2{0.5};
  double l3{0.25};

  while (ifs.peek() != -1) {
    double q1, q2, q3;
    ifs >> q1 >> q2 >> q3;

    // --- Your code here
    Eigen::Vector3d p;
    p << 0, 0, 1;
    p = transform_mat(q1, l1) * transform_mat(q2, l2) * transform_mat(q3, l3) *
        p;
    std::cout << std::setprecision(3) << p.x() << std::endl
              << p.y() << std::endl;

    // ---
  }
}