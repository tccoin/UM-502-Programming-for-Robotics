#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T square(T num) {
  return num * num;
}

int main() {
  double n1{5.5};
  int n2{4};
  cout << square<double>(n1) << endl;
  cout << square<int>(n1) << endl;
  cout << square<double>(n2) << endl;
  cout << square<int>(n2) << endl;
  cout << square<double>(n1) * square<int>(n1) << endl;
}