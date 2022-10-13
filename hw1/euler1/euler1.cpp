#include <iostream>
#include <string>

int main() {
  unsigned long answer = 0;
  // --- Your code here
  for (int i = 0; i < 1000; i++) {
    if (i % 3 == 0 || i % 5 == 0) answer += i;
  }

  // ---
  std::cout << answer << std::endl;
  return 0;
}