#include <iostream>
#include <vector>

using ObjMassPair =
    std::pair<std::string, double>;  // this defines the type ObjMassPair to be
                                     // std::pair<std::string, double>

// define the operator << here
// define a function that compares ObjMassPair objects here (for use by
// std::sort)
//  --- Your code here

bool cmp(ObjMassPair a, ObjMassPair b) { return a.second < b.second; }
std::ostream& operator<<(std::ostream& stream,
                         std::vector<ObjMassPair>& objects) {
  for (auto& obj : objects) {
    stream << obj.first << " " << obj.second << std::endl;
  }
  return stream;
}
// ---
