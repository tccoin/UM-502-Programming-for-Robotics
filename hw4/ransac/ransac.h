#include <eigen3/Eigen/Eigen>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

struct Plane {
  double a;
  double b;
  double c;
  double d;
};

struct FitResult {
  Plane plane;
  int n_inliers = -1;
};

void pretty_print(std::string const &input_filename, Plane const &plane) {
  std::cout << std::setprecision(3) << "--infile " << input_filename << " -a "
            << plane.a << " -b " << plane.b << " -c " << plane.c << " -d "
            << plane.d << '\n';
}

std::ostream &operator<<(std::ostream &os, Plane const &plane) {
  os << std::setprecision(3) << plane.a << " " << plane.b << " " << plane.c
     << " " << plane.d;
  return os;
}

Plane compute_plane_from_points(Eigen::Vector3d const &p0,
                                Eigen::Vector3d const &p1,
                                Eigen::Vector3d const &p2) {
  // 1. given p0, p1, and p2 form two vectors v1 and v2 which lie on the plane
  // 2. use v1 and v2 to find the normal vector of the plane `n`
  // 3. set a,b,c from the normal vector `n`
  // 4. set `d = -n.dot(p0)`
  // --- Your code here
  Eigen::Vector3d v1 = p0 - p1, v2 = p0 - p2;
  Eigen::Vector3d n = v1.cross(v2);
  Plane plane;
  plane.a = n.x();
  plane.b = n.y();
  plane.c = n.z();
  plane.d = -n.dot(p0);
  return plane;
  // ---
}

class BaseFitter {
 public:
  BaseFitter(int num_points) : mt(rd()), dist(0, num_points - 1) { mt.seed(0); }

  /**
   * Given all of the data `points`, select a random subset and fit a plane to
   * that subset. the parameter points is all of the points the return value is
   * the FitResult which contains the parameters of the plane (a,b,c,d) and the
   * number of inliers
   */
  virtual FitResult fit(Eigen::MatrixXd const &points) = 0;

  int get_random_point_idx() { return dist(mt); };

  double const inlier_threshold_{0.02};

 private:
  // These are for generating random indices, you don't need to know how they
  // work. Just use `get_random_point_idx()` and `points.row(rand_idx)`
  std::random_device rd;
  std::mt19937 mt;
  std::uniform_int_distribution<int> dist;
};

class AnalyticFitter : public BaseFitter {
 public:
  AnalyticFitter(int num_points) : BaseFitter(num_points) {}

  // by writing `override`, the compiler will check that this function actually
  // overrides something in the base class. Always use this to prevent mistakes
  // in the function signature!
  FitResult fit(Eigen::MatrixXd const &points) override {
    // 1. select 3 points from `points` randomly
    // 2. compute the equation of the plane (HINT: use
    // compute_plane_from_points)
    // 3. compute the `n_inliers` given that plane equation
    // (HINT: multiply the points matrix by the normal vector)
    // --- Your code here
    int i0 = 0, i1 = 0, i2 = 0;
    while (i0 == i1 || i0 == i2) {
      i0 = get_random_point_idx();
      i1 = get_random_point_idx();
      i2 = get_random_point_idx();
    }
    Eigen::Vector3d p0 = points.row(i0);
    Eigen::Vector3d p1 = points.row(i1);
    Eigen::Vector3d p2 = points.row(i2);
    Plane analytic_plane = compute_plane_from_points(p0, p1, p2);
    Eigen::Vector3d n;
    n << analytic_plane.a, analytic_plane.b, analytic_plane.c;
    Eigen::ArrayXd distances =
        ((points * n).array() + analytic_plane.d).abs() / n.norm();
    int n_inliers = (distances <= inlier_threshold_).count();
    // ---

    return {analytic_plane, n_inliers};
  }
};

class LeastSquaresFitter : public BaseFitter {
 public:
  LeastSquaresFitter(int num_points, int n_sample_points)
      : BaseFitter(num_points), n_sample_points_(n_sample_points) {}

  // You should override the `fit` method here
  // --- Your code here
  FitResult fit(Eigen::MatrixXd const &points) override {
    Eigen::MatrixXd points_sample(10, 3);
    for (int i = 0; i < 10; i++) {
      points_sample.row(i) = points.row(get_random_point_idx());
    }
    Eigen::MatrixXd A(n_sample_points_, 3);
    A.col(0) = points_sample.col(0);
    A.col(1) = points_sample.col(1);
    A.col(2) = Eigen::VectorXd::Ones(n_sample_points_);
    Eigen::VectorXd b = points_sample.col(2);
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    Plane analytic_plane{x.x(), x.y(), -1, x.z()};
    Eigen::Vector3d n;
    n << analytic_plane.a, analytic_plane.b, analytic_plane.c;
    Eigen::ArrayXd distances =
        ((points * n).array() + analytic_plane.d).abs() / n.norm();
    int n_inliers = (distances <= inlier_threshold_).count();
    return {analytic_plane, n_inliers};
  }
  // ---

  int const n_sample_points_;
};

Plane ransac(BaseFitter &fitter, Eigen::MatrixXd const &points) {
  // --- Your code here
  FitResult best_result, result;
  best_result.n_inliers = 0;
  for (int i = 0; i < 300; i++) {
    result = fitter.fit(points);
    if (result.n_inliers >= best_result.n_inliers) {
      best_result = result;
    }
  }
  // ---

  // HINT: the number of inliers should be between 20 and 80 if you did
  // everything correctly
  std::cout << best_result.n_inliers << std::endl;
  return best_result.plane;
}