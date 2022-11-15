#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
struct JointLimit {
  double lower_;
  double upper_;
  JointLimit(double lower, double upper) : lower_(lower), upper_(upper) {}
};
double clip(double joint_position, JointLimit const &joint_limit) {
  if (joint_position < joint_limit.lower_) {
    return joint_limit.lower_;
  } else if (joint_position > joint_limit.upper_) {
    return joint_limit.upper_;
  } else {
    return joint_position;
  }
}
void enforce_joint_limits(std::map<std::string, JointLimit> const &joint_limits,
                          std::map<std::string, double> &q) {
  // create a for-loop over "q" with the loop variable "kv" auto const&
  for (auto const &kv : q) {
    std::string const joint_name = kv.first;
    double joint_position = kv.second;
    JointLimit const joint_limit = joint_limits.at(joint_name);
    q[joint_name] = clip(joint_position, joint_limit);
  }
}
int main() {
  std::vector<double> joint_values{0, 0.2, 0.5, -0.4, 0.5};
  // create a ranged-for loop over joint_values with loop variable named
  // "joint_i". IMPORTANT!!!! we want to modify the joint values!
  for (auto &joint_i : joint_values) {
    joint_i *= 2;
  }
  std::map<std::string, JointLimit> joint_limits{
      {"joint1", JointLimit{0, M_PI}},
      {"joint2", JointLimit{-M_PI, M_PI}},
      {"joint3", JointLimit{-M_PI, 0}},
      {"joint4", JointLimit{-2 * M_PI, 2 * M_PI}},
      {"joint5", JointLimit{-2 * M_PI, 2 * M_PI}},
  };
  std::map<std::string, double> q{
      {"joint1", -2.0},
      {"joint2", 2.0},
      {"joint3", 2.0},
      {"joint4", 3.0},
  };
  enforce_joint_limits(joint_limits, q);
  double final_answer = 0;
  // create a ranged-for loop over "q" with loop variable named "kv"
  for (auto kv : q) {
    final_answer += kv.second;
  }
  // create a ranged-for loop over "joint_values" with loop variable
  // named joint_i
  for (auto joint_i : joint_values) {
    final_answer += joint_i;
  }
  std::cout << final_answer << "\n";
  return 0;
}