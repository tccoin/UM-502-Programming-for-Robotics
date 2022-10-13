#include <fstream>
#include <iostream>
// --- Your code here
#include <functional>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
// ---

using namespace std;
int main() {
  ifstream infile("input.txt");
  ofstream outfile("output.txt");

  // Read in each line from the input file,
  // perform the specified operation on the numbers,
  // and write the results to the ouputfile.
  // Remember to check if the specified operation is possible!
  //  --- Your code here
  vector<double> nums;
  string line;
  char op;
  while (!infile.eof()) {
    getline(infile, line);
    if (line.length() == 0) {
      break;
    }
    op = line.back();
    line.pop_back();
    line.pop_back();
    stringstream numStream(line);
    nums.clear();
    double tmp;
    while (!numStream.eof()) {
      numStream >> tmp;
      nums.push_back(tmp);
    }
    if (op == '/' && nums.size() != 2 || op == '/' && nums[1] == 0) {
      outfile << "ERROR" << endl;
    } else {
      double ans;
      if (op == '+') {
        ans = accumulate(nums.begin(), nums.end(), 0.0, plus<double>());
      } else if (op == '*') {
        ans = accumulate(nums.begin(), nums.end(), 1.0, multiplies<double>());
      } else if (op == '/') {
        ans = nums[0] / nums[1];
      }
      outfile << ans << endl;
    }
  }

  // ---
  return 0;
}
