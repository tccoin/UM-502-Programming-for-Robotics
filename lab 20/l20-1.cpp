#include <cmath>
#include <iostream>
#include <vector>
class Point {
 public:
  Point(double x, double y) : x(x), y(y) {}
  double x, y;
};
using Problem = std::vector<Point>;
using Assignment = std::vector<int>;
class Solution {
 public:
  Solution(size_t N) {
    // default solution; each solution must be valid
    for (size_t i = 0; i < N; ++i) {
      order.push_back(i);
    }
  }
  // the order in which the points are visited; note that we never need to visit
  // a node twice therefore the assignment is a permutation of 0,1,...,N-1
  Assignment order;
  double cost;
};

double distance(const Point& a, const Point& b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}

double scoreAssignment(const Problem& points, const Assignment& order) {
  double score = 0;
  for (int i = 1; i < order.size(); i++) {
    score += distance(points[order[i - 1]], points[order[i]]);
  }
  return score;
}

Assignment perturbAssignment(Assignment order) {
  // randomly swap the order of two items
  // fine if sometimes you swap an element with itself
  int i0 = rand() % order.size();
  int i1 = rand() % order.size();
  int tmp = order[i0];
  order[i0] = order[i1];
  order[i1] = tmp;
  std::cout << std::endl;
  return order;
}

class SimulatedAnnealingParameters {
 public:
  double maxTemperature;
  double deltaTemperature;
  double finishTemperature;
};
Solution simulatedAnnealing(const Problem& problem, Solution sol,
                            SimulatedAnnealingParameters params) {
  for (double t = params.maxTemperature; t > params.finishTemperature;
       t *= params.deltaTemperature) {
    // --- Your code here
    Assignment next = perturbAssignment(sol.order);
    double score = scoreAssignment(problem, next);
    if (score < sol.cost || rand() / RAND_MAX < exp((sol.cost - score) / t)) {
      sol.order = next;
      sol.cost = score;
    }

    std::cout << "cur cost " << sol.cost << " sample cost " << score
              << std::endl;
    std::cout << "order: ";
    for (auto i : sol.order) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
    // ---
  }
  return sol;
}

int main() {
  Problem prob;
  prob.emplace_back(0, 0);
  prob.emplace_back(5, 5);
  prob.emplace_back(-2, 3);
  prob.emplace_back(4, 1);
  prob.emplace_back(3, 4);
  prob.emplace_back(-4, -2);
  prob.emplace_back(2, -4);
  Solution sol(prob.size());
  // solution of default assignment
  sol.cost = scoreAssignment(prob, sol.order);
  std::cout << sol.cost << std::endl;
  SimulatedAnnealingParameters params{100000, 0.995, 0.001};
  auto saSolution = simulatedAnnealing(prob, sol, params);
  std::cout << "simulated annealing solution\ncost " << saSolution.cost
            << std::endl;
  for (const auto& i : saSolution.order) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  for (const auto& i : saSolution.order) {
    std::cout << prob[i].x << ' ' << prob[i].y << std::endl;
  }
}