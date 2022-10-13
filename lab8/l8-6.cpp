#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <utility>
struct JointLimit {
  double lower_;
  double upper_;
  JointLimit(double lower, double upper) : lower_(lower), upper_(upper) {}
};
void enforce_joint_limits(std::map<std::string, JointLimit> const &joint_limits,
                          std::map<std::string, double> &q) {
  // --- Your Code Here
  // ---
}
int main() {
  std::map<std::string, JointLimit> joint_limits;
  std::map<std::string, double> q;
  // --- Your Code Here
  joint_limits.insert({"joint1", JointLimit{-M_PI, M_PI}});
  // ---
  enforce_joint_limits(joint_limits, q);
  for (std::pair<std::string, double> const &kv : q) {
    std::cout << kv.first << " " << kv.second << "\n";
  }
  return 0;
}