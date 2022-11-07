#include <math.h>

#include <stdexcept>

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

// --- Your code here

double norm(State& a, State& b) {
  double sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return sqrt(sum);
}

// ---

Control estimate_control_gradient(State goal_state, State current_state,
                                  Control control) {
  // formulate a cost function f(goal, x, u) and find the gradient with respect
  // to u at the given goal, x, u if you're estimating gradient using some step,
  // use h
  auto h = 0.001;
  // --- Your code here

  Control gradient;
  Control control_plus_h;
  State fx = true_dynamics(current_state, control);
  control_plus_h.speed = control.speed + h;
  control_plus_h.turn = control.turn;
  State fx1 = true_dynamics(current_state, control_plus_h);
  gradient.speed = (norm(fx1, goal_state) - norm(fx, goal_state)) / h;
  control_plus_h.speed = control.speed;
  control_plus_h.turn = control.turn + h;
  State fx2 = true_dynamics(current_state, control_plus_h);
  gradient.turn = (norm(fx2, goal_state) - norm(fx, goal_state)) / h;
  return gradient;

  // ---
}
