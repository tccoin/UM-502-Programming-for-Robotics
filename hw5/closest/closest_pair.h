#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  int id;
  double x, y;
};

double dist(const Point& p1, const Point& p2) {
  auto dx = p1.x - p2.x;
  auto dy = p1.y - p2.y;
  return std::sqrt(dx * dx + dy * dy);
}

// --- Your code here

Point fail_point0{-2, -1000, -1000}, fail_point1{-1, 1000, 1000};

std::pair<Point, Point> closest_pair_bf(const std::vector<Point>& points) {
  std::pair<Point, Point> best_pair{fail_point0, fail_point1};
  double min_dist = 100000, tmp_dist;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      tmp_dist = dist(points[i], points[j]);
      if (tmp_dist < min_dist) {
        min_dist = tmp_dist;
        best_pair = {points[i], points[j]};
      }
    }
  }
  if (best_pair.first.id > best_pair.second.id) {
    best_pair = {best_pair.second, best_pair.first};
  }
  return best_pair;
}

std::pair<Point, Point> closest_pair_sorted(const std::vector<Point>& points) {
  if (points.size() <= 5) {
    return closest_pair_bf(points);
  }
  // std::cout << "===========" << std::endl;
  // for (auto& point : points) {
  //   std::cout << point.id << " ";
  // }
  // std::cout << std::endl;
  int m = (points.size()) / 2;
  std::vector<Point> left_points(points.begin(), points.begin() + m);
  std::vector<Point> right_points(points.begin() + m, points.end());
  std::pair<Point, Point> left_pair = closest_pair_sorted(left_points);
  std::pair<Point, Point> right_pair = closest_pair_sorted(right_points);
  double left_dist = dist(left_pair.first, left_pair.second);
  double right_dist = dist(right_pair.first, right_pair.second);
  double min_dist = std::min(left_dist, right_dist);
  std::vector<Point> middle_points;
  for (auto& point : points) {
    if (std::abs(point.x - points[m].x) < min_dist) {
      middle_points.push_back(point);
    }
  }
  if (middle_points.size() < points.size()) {
    std::pair<Point, Point> middle_pair = closest_pair_bf(middle_points);
    double middle_dist = dist(middle_pair.first, middle_pair.second);
    if (middle_dist < min_dist) {
      return middle_pair;
    } else {
      return min_dist == left_dist ? left_pair : right_pair;
    }
  } else {
    return min_dist == left_dist ? left_pair : right_pair;
  }
}

// ---

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
  // --- Your code here
  std::vector<Point> points_sorted;
  points_sorted.insert(points_sorted.end(), points.begin(), points.end());
  std::sort(points_sorted.begin(), points_sorted.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; });
  return closest_pair_sorted(points_sorted);
  // ---
}