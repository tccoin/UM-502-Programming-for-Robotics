#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  double mass, w, h, d;
  std::ifstream ifs("inertia_input.txt");
  ifs >> mass;
  ifs >> w;
  ifs >> h;
  ifs >> d;
  // you'll need to store the outputs in variables Ih, Iw, and Id.
  // --- Your code here
  double Ih = mass / 12 * (w * w + d * d);
  double Iw = mass / 12 * (h * h + d * d);
  double Id = mass / 12 * (w * w + h * h);

  // ---
  std::cout << "<ixx>" << Ih << "</ixx>\n";
  std::cout << "<iyy>" << Iw << "</iyy>\n";
  std::cout << "<izz>" << Id << "</izz>\n";
  return 0;
}