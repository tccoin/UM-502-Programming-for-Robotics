#include <CGAL/MP_Float.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
#include <CGAL/Quotient.h>
#include <math.h>

#include <eigen3/Eigen/Eigen>
#include <stdexcept>
typedef CGAL::MP_Float ET;
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

// state and control space sizes
constexpr int NX = 3;
constexpr int NU = 2;

class State {
 public:
  double x, y, heading;
  double& operator[](int key) {
    switch (key) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return heading;
      default:
        throw std::out_of_range("key out of range");
    }
  }
  const double& operator[](int key) const { return this->operator[](key); }
};

class Control {
 public:
  double speed, turn;
  double& operator[](int key) {
    switch (key) {
      case 0:
        return speed;
      case 1:
        return turn;
      default:
        throw std::out_of_range("key out of range");
    }
  }
  const double& operator[](int key) const { return this->operator[](key); }
};

class XU {
 public:
  State x;
  Control u;
  double& operator[](int key) {
    if (key < 3) {
      return x[key];
    } else {
      return u[key - 3];
    }
  }
};

State true_dynamics(State x, Control u) {
  auto t = 0.1;
  auto next_x = x;
  next_x.x += u.speed * t * cos(x.heading);
  next_x.y += u.speed * t * sin(x.heading);
  next_x.heading += u.turn * t;
  return next_x;
}

class EstimatedDynamics {
 public:
  // x_next = Sx + Bu
  Eigen::Matrix<double, NX, NX> S;
  Eigen::Matrix<double, NX, NU> B;
};

EstimatedDynamics linearize_dynamics_numerically(State state,
                                                 Control reference_control,
                                                 double h = 0.1) {
  // numerically estimate the Jacobian of true_dynamics using finite differences
  // --- Your code here
  EstimatedDynamics J;
  State state_h;
  Control control_h;
  State ref_state = true_dynamics(state, reference_control);
  State tmp_state;
  for (int i = 0; i < NX; i++) {
    state_h = state;
    state_h[i] += h;
    tmp_state = true_dynamics(state_h, reference_control);
    for (int j = 0; j < NX; j++) {
      J.S(j, i) = (tmp_state[j] - ref_state[j]) / h;
    }
  }
  for (int i = 0; i < NU; i++) {
    control_h = reference_control;
    control_h[i] += h;
    tmp_state = true_dynamics(state, control_h);
    for (int j = 0; j < NX; j++) {
      J.B(j, i) = (tmp_state[j] - ref_state[j]) / h;
    }
  }
  return J;
  // ---
}

Control optimize_single_action(State goal_state, State current_state,
                               EstimatedDynamics AB, Control u_min,
                               Control u_max) {
  // produce the single best control within the control bounds (inclusive)
  // minimize the resulting L-2 norm between next state and goal state

  // using QP
  Program qp(CGAL::SMALLER);
  // we will be explicitly specifying bounds so don't have to worry about the
  // other constructor parameters
  Eigen::VectorXd x(NX), x_g(NX);
  for (int i = 0; i < NX; i++) {
    x(i) = current_state[i];
    x_g(i) = goal_state[i];
  }
  Eigen::MatrixXd D = AB.B.transpose() * AB.B;
  Eigen::VectorXd b = -1 * (AB.S * x - x_g);
  Eigen::VectorXd ct = -2 * b.transpose() * AB.B;
  double c0 = b.transpose() * b;

  // setup the QP
  // remember to specify 2D instead of just D
  // it also only expects the upper triangular part of D to be specified (since
  // it's symmetric)
  // --- Your code here
  for (int i = 0; i < NU; i++) {
    for (int j = 0; j <= i; j++) {
      qp.set_d(i, j, 2 * D(i, j));
    }
  }
  for (int i = 0; i < NU; i++) {
    qp.set_c(i, ct(i));
  }
  qp.set_c0(c0);
  qp.set_u(0, true, u_max[0]);
  qp.set_u(1, true, u_max[1]);
  qp.set_l(0, true, u_min[0]);
  qp.set_l(1, true, u_min[1]);

  // ---

  Solution s = CGAL::solve_quadratic_program(qp, ET{});
  auto it = s.variable_values_begin();
  double u1 = CGAL::to_double(*it);
  double u2 = CGAL::to_double(*(++it));
  Control u{u1, u2};
  return u;
}