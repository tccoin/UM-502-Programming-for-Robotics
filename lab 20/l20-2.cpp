#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace std;
using Assignment = Eigen::Matrix<double, 4, 1>;
class Problem {
 public:
  Eigen::Matrix<double, 5, 1> requiredHours;
  Eigen::Matrix<double, 4, 1> costPerRobot;
  Eigen::Matrix<double, 5, 4> robotCapabilities;
};
double penaltyPerHour = 200;
double fitness(const Problem& prob, const Assignment& hours) {
  // --- Your code here
  cout << "hours: "
       << (prob.requiredHours - prob.robotCapabilities * hours).cwiseMax(0)
       << endl;
  double cost = 200 * (prob.requiredHours - prob.robotCapabilities * hours)
                          .cwiseMax(0)
                          .array()
                          .sum();
  cout << "penalty: " << cost << endl;
  cost += hours.transpose() * prob.costPerRobot;
  cout << "cost: " << cost << endl;
  return cost;
  // ---
}

class Solution {
 public:
  Assignment hours;
  double cost;
};
bool compareSolution(const Solution& a, const Solution& b) {
  return a.cost < b.cost;
}
using Population = std::vector<Solution>;

Solution crossOver(const Solution& a, const Solution& b) {
  // your code here
  Assignment c;
  c << a.hours(0), a.hours(1), b.hours(2), b.hours(3);
  return {c, 0};
}
void mutate(Solution& a) {
  // your code here
  for (auto& i : a.hours) {
    i += rand() * 0.2 / RAND_MAX - 0.1;
  }
  a.hours = a.hours.cwiseMax(0);
}

int main() {
  Problem prob;
  prob.requiredHours << 10, 25, 15, 5, 20;
  prob.costPerRobot << 75, 128, 70, 34;
  // --- Your code here (populate up robotCapabilities)
  prob.robotCapabilities << 1.6, 7.2, 3.7, 0.1, 3.5, 2.1, 3.2, 0.15, 0.1, 7.1,
      2.9, 0.1, 2.3, 3.2, 3.4, 0.15, 6.1, 0.1, 4.9, 0.1;
  // ---
  Assignment test;
  test << 2.0, 2, 2.5, 2.0;
  std::cout << fitness(prob, test) << std::endl;
  // ---
  const auto populationSize = 1000;
  Population population(populationSize);
  double hourMax = 3;
  for (int i = 0; i < populationSize; ++i) {
    population[i].hours << (double)rand() / RAND_MAX * 3,
        (double)rand() / RAND_MAX * 3, (double)rand() / RAND_MAX * 3,
        (double)rand() / RAND_MAX * 3;
    population[i].cost = fitness(prob, population[i].hours);
  }
  // 100 iterations of evoluation
  for (int k = 0; k < 100; ++k) {
    std::sort(population.begin(), population.end(), compareSolution);
    int cutoffIndex = populationSize / 10;
    Population nextPopulation(populationSize);
    for (int i = 0; i < populationSize; ++i) {
      const Solution& a = population[rand() % cutoffIndex];
      const Solution& b = population[rand() % cutoffIndex];
      nextPopulation[i] = crossOver(a, b);
      mutate(nextPopulation[i]);
      nextPopulation[i].cost = fitness(prob, nextPopulation[i].hours);
    }
    population = nextPopulation;
  }
  std::sort(population.begin(), population.end(), compareSolution);
  std::cout << "best in population\n" << population[0].hours << std::endl;
  std::cout << "cost: " << population[0].cost << std::endl;
}