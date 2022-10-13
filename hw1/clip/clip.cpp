#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  // check whether a value is within a given range, and if the “clip” flag is
  // set, and it’s outside the range, clip it (3 args from stdin)
  std::ifstream ifs("clip_input.txt");
  if (ifs.fail()) {
    std::cout << "Missing clip_input.txt file\n";
    return 0;
  }
  double min_value, max_value, value;
  bool clip;
  std::string line;
  while (!ifs.eof()) {
    ifs >> min_value;
    ifs >> max_value;
    ifs >> value;
    ifs >> clip;
    // --- Your code here
    double out_value = value;
    if (clip) out_value = std::max(std::min(out_value, max_value), min_value);

    // ---
    std::cout << out_value << std::endl;
  }
  return 0;
}