#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  // HINT: consider using std::to_string and std::reverse
  unsigned long largest_palandrome{0};
  // --- Your code here
  unsigned long product;
  std::string a, b;
  bool found = false;
  for (int i = 999; i >= 100; i--) {
    for (int j = i; j >= 100; j--) {
      product = i * j;
      a = std::to_string(product);
      b = a;
      std::reverse(b.begin(), b.end());
      if (a == b && product > largest_palandrome) {
        largest_palandrome = product;
      }
    }
  }

  // ---
  std::cout << largest_palandrome << std::endl;
  return 0;
}