#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
  double a, b, c;
  std::cout << "Type in a, b, and c. Press 'Enter' between each\n";
  std::cin >> a;
  std::cin >> b;
  std::cin >> c;
  std::cout << std::setprecision(4);
  // --- Your code here
  double delta = b * b - 4 * a * c;
  if (delta > 0) {
    std::cout << (-b - sqrt(delta)) / 2 / a << std::endl;
    std::cout << (-b + sqrt(delta)) / 2 / a;
  } else if (delta == 0) {
    std::cout << ((b == 0) ? 0 : (-b / 2 / a));
  } else {
    std::cout << "None";
  }

  // ---
  return 0;
}