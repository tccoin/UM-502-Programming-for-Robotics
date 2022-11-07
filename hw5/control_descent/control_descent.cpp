#include <fstream>
#include "control_descent.h"

Control optimize_single_action(State goal_state, State current_state, Control u_min, Control u_max) {
    // produce the single best control within the control bounds (inclusive)
    // minimize the resulting L-2 norm between next state and goal state

    // using gradient descent
    auto step_size = 0.1;
    auto iterations = 500;
    Control u {0,0};
    for (int i = 0; i < iterations; ++i) {
        Control gradient = estimate_control_gradient(goal_state, current_state, u);

        u.speed -= gradient.speed * step_size;
        u.turn -= gradient.turn * step_size;

        for (int i = 0; i < 2; ++i) {
            u[i] = std::min(std::max(u[i], u_min[i]), u_max[i]);
        }
    }
    return u;
}

int main() {
    // get initial conditions and goal from input.txt
    
    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    Control u_min {0, -2};
    Control u_max {1, 2};

    while (input.peek() != EOF) {
        State current_state;
        State goal_state;
        input >> current_state.x >> current_state.y >> current_state.heading;
        input >> goal_state.x >> goal_state.y >> goal_state.heading;

        for (int i = 0; i < 40; ++i) {
            Control u = optimize_single_action(goal_state, current_state, u_min, u_max);
            current_state = true_dynamics(current_state, u);
            output << u.speed << ' ' << u.turn << std::endl;
        }
    }
}