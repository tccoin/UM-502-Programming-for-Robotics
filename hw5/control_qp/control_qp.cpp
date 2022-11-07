#include "control_qp.h"
#include <fstream>

int main() {
    // get initial conditions and goal from input.txt

    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    Control u_min{0, -2};
    Control u_max{1, 2};

    while (input.peek() != EOF) {
        State current_state;
        State goal_state;
        input >> current_state.x >> current_state.y >> current_state.heading;
        input >> goal_state.x >> goal_state.y >> goal_state.heading;

        for (int i = 0; i < 40; ++i) {
            auto dynamics =
                linearize_dynamics_numerically(current_state, Control{0, 0});
            Control u = optimize_single_action(goal_state, current_state, dynamics,
                                               u_min, u_max);
            current_state = true_dynamics(current_state, u);
            output << u.speed << ' ' << u.turn << std::endl;
            output << dynamics.S << std::endl;
            output << dynamics.B << std::endl;
        }
    }
}