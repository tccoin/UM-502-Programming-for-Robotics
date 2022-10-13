#include <iostream>

int main() {
  // --- Your code here
  int sum1 = 0, sum2 = 0;
  for (int i = 1; i <= 100; i++) {
    sum1 += i * i;
    sum2 += i;
  }
  sum2 *= sum2;
  int difference = sum2 - sum1;

  // ---
  std::cout << difference << std::endl;
  return 0;
}