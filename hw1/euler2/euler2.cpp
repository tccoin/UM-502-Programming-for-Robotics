#include <iostream>
#include <string>

int main() {
  // you'll need to store the answer in a variable named 'sum'
  // --- Your code here
  int a = 1, b = 2, sum = 2, c = a + b;
  while (c <= 4000000) {
    if (c % 2 == 0) sum += c;
    (a < b ? a : b) = c;
    c = a + b;
  }

  // ---
  std::cout << sum << std::endl;
  return 0;
}