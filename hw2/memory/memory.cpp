#include <fstream>
#include <iostream>
// below are some includes that are hints for what could make things easier
#include <algorithm>
#include <string>
#include <vector>

void processLine(std::string& line, int lineNumber, int* counter) {
  // line is passed in by reference, so you can modify it directly
  // do not return anything from this function
  // --- Your code here
  for (char& ch : line) {
    if (ch == 'e') {
      ch = '3';
      *counter += 3 * lineNumber;
    } else if (ch == 'l') {
      ch = '1';
      *counter += lineNumber;
    } else if (ch == 't') {
      ch = '7';
      *counter += 7 * lineNumber;
    }
  }
  // ---
}

int* createCounter() {
  // this is a contrived function to get you more familiar with heap allocation
  // if you return a pointer to a local variable (on the stack), that value will
  // be invalid after the return and accessing it will be unexpected behavior
  // (probably a segfault) remember to initialize it to 0
  // --- Your code here
  return new int(0);

  // ---
}

int main() {
  // you will need to read the API of std::ofstream and std::ifstream
  std::ifstream input{"input.txt"};
  std::vector<std::string> lines;
  std::string line;

  // create a reference to the pointed value
  // references can be used more conveniently than pointers
  // note that the processLine function takes counter as a pointer, so you have
  // to address it with & contrived example to get you more familiar with going
  // between references and pointers usually there will not be so many
  // unnecessary conversions
  int& counter = *createCounter();

  // --- Your code here
  int i = 0;
  while (!input.eof()) {
    std::getline(input, line);
    processLine(line, i, &counter);
    lines.push_back(line);
    i++;
  }
  // ---

  // output
  // --- Your code here
  std::ofstream output{"output.txt"};
  for (int j = lines.size() - 1; j > -1; j--) {
    output << lines[j] << std::endl;
  }
  output << counter << std::endl;
  // ---

  delete &counter;
}