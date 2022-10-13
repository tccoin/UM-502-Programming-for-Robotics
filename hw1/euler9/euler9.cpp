#include <iostream>

int euler9() {
  // --- Your code here
  int a, b, c;
  for (a = 1; a < 1000; a++) {
    for (b = a; b < 1000; b++) {
      if (a * a + b * b > 1000000) break;
      if (2 * a * b - 2000 * a - 2000 * b + 1000000 == 0) {
        return a * b * (1000 - a - b);
      }
    }
  }
  // ---
}

int main() {
  // This code is a lot cleaner if you write it as a function, because you can
  // use `return` once you find the answer
  int const product = euler9();
  std::cout << product << std::endl;
  return 0;
}