#include <iostream>
using namespace std;
int main() {
  int count;
  int a = 0;
  int N;
  N = 10;
  count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = N; j > i; j--) {
      a = a + i + j;
      count++;
    }
  }
  cout << "count: " << count << endl;
  N = 100;
  count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = N; j > i; j--) {
      a = a + i + j;
      count++;
    }
  }
  cout << "count: " << count << endl;
  N = 1000;
  count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = N; j > i; j--) {
      a = a + i + j;
      count++;
    }
  }
  cout << "count: " << count << endl;
}