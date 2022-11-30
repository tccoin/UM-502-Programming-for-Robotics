#include "test.h"

Robot::Robot(std::string const &name, int dof) : name_(name), dof_(dof) {
  std::cout << "building robot " << name_ << " with " << dof_ << " joints\n";
}

int main() {
  std::vector<Robot> robots;
  robots.reserve(3);
  robots.emplace_back("aaa", 111);
  robots.emplace_back("bbb", 111);
  robots.emplace_back("ccc", 111);
  return 0;
}