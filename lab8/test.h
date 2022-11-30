#include <iostream>
#include <vector>

class Robot {
 public:
  Robot(std::string const &name, int dof);

 private:
  int dof_;
  std::string name_;
};