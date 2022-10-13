#include <iostream>

class Robot {
  int links;

 public:
  Robot() : links(0){};
  Robot(int l) : links(l){};
  int getLinks() const { return links; }
};
class PandaArm : public Robot {
 public:
  PandaArm() : Robot{7} {}
};
int main() {
  PandaArm p;
  std::cout << p.getLinks() << std::endl;
}