#include <iostream>
#include <vector>

#define ERROR_MESSAGE \
  std::invalid_argument("Error: vectors must be the same size")

// --- Your code here

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& nums) {
  stream << "[";
  if (nums.size() > 0) {
    for (int i = 0; i < nums.size() - 1; i++) {
      stream << nums[i] << ", ";
    }
    stream << nums.back();
  }
  stream << "]";
  return stream;
}

template <typename T, typename S>
std::vector<double> operator+(std::vector<T> a, const std::vector<S>& b) {
  if (a.size() != b.size()) {
    throw ERROR_MESSAGE;
  }
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] + b[i];
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator-(std::vector<T> a, const std::vector<S>& b) {
  if (a.size() != b.size()) {
    throw ERROR_MESSAGE;
  }
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] - b[i];
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator*(std::vector<T> a, const std::vector<S>& b) {
  if (a.size() != b.size()) {
    throw ERROR_MESSAGE;
  }
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] * b[i];
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator*(std::vector<T> a, const S& b) {
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] * b;
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator*(const S& b, std::vector<T> a) {
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] * b;
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator/(std::vector<T> a, const S& b) {
  std::vector<double> ans(a.size(), 0);
  for (int i = 0; i < a.size(); i++) {
    ans[i] = a[i] / b;
  }
  return ans;
}

template <typename T, typename S>
std::vector<double> operator,(std::vector<T> a, const std::vector<S>& b) {
  std::vector<double> ans;
  for (auto i : a) {
    ans.push_back(i);
  }
  for (auto i : b) {
    ans.push_back(i);
  }
  return ans;
}

// ---
