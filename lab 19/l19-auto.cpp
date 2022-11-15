#include <array>
#include <iostream>
#include <map>

std::array<unsigned long, 500> pentagonal;

auto partition(unsigned long n) {
  static std::map<unsigned long, unsigned long> memoization = {{0, 1}, {1, 1}};
  auto const it = memoization.find(n);
  if (it != memoization.cend()) {
    return it->second;
  }
  auto partitions{0l};
  for (auto k{1};; ++k) {
    auto const sign = ((k + 1) / 2) % 2 == 0 ? -1 : 1;
    auto const pent = pentagonal[k];
    if (n < pent) {
      break;
    }
    partitions += sign * partition(n - pent);
  }
  partitions = partitions % 1'000'000;
  if (partitions < 0) {
    partitions += 1'000'000;
  }
  memoization.emplace(n, partitions);
  return static_cast<unsigned long>(partitions);
}

auto problem() {
  // pre-compute pentagonal numbers
  auto k{1};
  for (auto j{1ul}; j < pentagonal.size(); ++j) {
    pentagonal[j] = static_cast<unsigned long>(k * (3 * k - 1) / 2);
    if (k > 0) {
      k = -k;
    } else {
      k = -k + 1;
    }
  }
  auto n{0ul};
  while (true) {
    auto const p = partition(n);
    if (p == 0) {
      return n;
    }
    ++n;
  }
}
auto main() {
  // Solves Project Euler 78: https://projecteuler.net/problem=78
  auto solution = problem();
  std::cout << solution << '\n';
  return 0;
}