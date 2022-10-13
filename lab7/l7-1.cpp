#include <iostream>
#include <vector>

template <typename T>
T sum(const std::vector<T>& nums) {
  double sum = 0;
  for (int i = 0; i < nums.size(); ++i) {
    sum += nums[i];
  }
  return sum;
}
int main() {
  std::vector<int> n1{2, 4, 6, 8};
  std::vector<double> n2{3.0, -2.2, 5.5, 6.1};
  std::cout << sum(n1) << std::endl;
  std::cout << sum(n2) << std::endl;
}