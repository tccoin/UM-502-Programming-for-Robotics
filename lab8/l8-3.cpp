#include <iostream>
#include <vector>
class Robot {
 public:
  Robot(std::string const &name, int dof) : name_(name), dof_(dof) {
    std::cout << "building robot " << name_ << " with " << dof_ << " joints\n";
  }
  Robot(Robot const &other)
      : Robot(other.name_, other.dof_) {}  // copy constructor
 private:
  int dof_;
  std::string name_;
};
int main() {
  std::vector<Robot> robots;
  robots.reserve(3);  // this pre-allocates SPACE for 3 robots, but does NOT
                      // allocate any Robot objects
  // call push_back and emplace_back here
  //   robots.push_back(Robot("aaa", 111));
  //   robots.push_back(Robot("aaa", 222));
  //   robots.push_back(Robot("aaa", 333));
  robots.emplace_back("aaa", 111);
  robots.emplace_back("bbb", 111);
  robots.emplace_back("ccc", 111);
  // you can use whatever values you like for name and dof
  return 0;
}