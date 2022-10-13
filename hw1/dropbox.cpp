#include <chrono>
#include <iostream>

int main() {
  std::cout << std::chrono::system_clock::to_time_t(
                   std::chrono::system_clock::now())
            << std::endl;
  return 0;
}