#include <iostream>
#include <vector>

#include "operators.h"

using namespace std;
int main() {
  // you can test your operators here
  // feel free to change any of the code below
  // the expected cout output for the code is given to you in cout_output.txt
  vector<int> v_int = {1, 2, 7, 8};
  vector<double> v_double = {1.0, 2, 2.4, 7.2, 8};
  vector<double> v_double2 = {2, 2.4, 7.2, 8};
  vector<float> v_float = {-9.2, -3.4};
  int aaa = 3;

  cout << "v_int= " << v_int << endl;
  cout << "v_double= " << v_double << endl;
  cout << "v_float= " << v_float << endl;
  cout << "v_int+v_int= " << v_int + v_int << endl;
  cout << "v_double+v_double= " << v_double + v_double << endl;
  cout << "v_double-v_double= " << (v_double - v_double) << endl;
  cout << "v_double*v_double= " << (v_double * v_double) << endl;
  cout << "v_double*double= " << (v_double * 3.0) << endl;
  cout << "v_double*int= " << (v_double * aaa) << endl;
  cout << "double*v_double= " << (3.0 * v_double) << endl;
  cout << "v_double/double= " << (v_double / 3.0) << endl;
  cout << "v_double,v_double2= " << (v_double, v_double2) << endl;
  cout << "v_int,v_double2= " << (v_int, v_double2) << endl;
  try {
    cout << "v_double+v_double2= ";
    cout << v_double + v_double2 << endl;
  } catch (const std::invalid_argument &e) {
    // do nothing
    cout << e.what() << endl;
  }

  return 0;
}
