#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Array {
 public:
  Array(int len) { data = vector<T>(len); }
  T& operator[](int index);
  const T& operator[](int index) const;
  int size() const;
  vector<T> data;
};

template <typename T>
int Array<T>::size() const {
  return data.size();
}

template <typename H>

H& Array<H>::operator[](int i) {
  return data[i];
}

template <typename C>
const C& Array<C>::operator[](int i) const {
  return data[i];
}

template <typename T>
void printArray(const T& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
}
int main() {
  Array<int> a(3);
  a[1] = 5;
  printArray(a);
  Array<double> b(5);
  b[0] = 2.2;
  printArray(b);
}