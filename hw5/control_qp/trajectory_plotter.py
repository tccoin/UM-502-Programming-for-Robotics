import matplotlib.pyplot as plt
import numpy as np
import os.path
import time
import argparse

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))


class StateIndices:
    X = 0
    Y = 1
    HEADING = 2


class ControlIndices:
    SPEED = 0
    TURN = 1


class CarEnvironment:
    """Simplified Dubin's car environment"""

    def __init__(self, eval=False):
        # plotting
        if not eval:
            self.fig = plt.gcf()
            self.ax = plt.gca()
            self.ax.set_xlim(-2, 2)
            self.ax.set_ylim(-2, 2)
            self.ax.set_xlabel('x')
            self.ax.set_ylabel('y')
            self.ax.set_aspect('equal')
            self.car_artists = {}

            self.fig.suptitle('Press Space Bar to End Run', fontsize=14, fontweight='bold')

            # set up the space bar call back for ending early
            def onpress(event):
                global bKeepRunning

                if event.key == ' ':
                    if bKeepRunning == False:
                        # plot is already stopped, exit
                        exit()
                    else:
                        bKeepRunning = False
                        print('Ending the run')
                        # self.fig.suptitle('Press Space Bar to Close Program', fontsize=14, fontweight='bold', color='red')

            self.fig.canvas.mpl_connect('key_press_event', onpress)

            plt.ion()
            plt.show()
        self.state_history = []

    def visualize_state(self, state, name='state', color=(0, 0, 0), plot_trail=True):
        """Draw a state"""
        car_artists = self.car_artists.get(name, [])
        for artist in car_artists:
            artist.remove()
        car_artists = []

        if plot_trail and name == 'state':
            self.state_history.append(state)
            xs, ys, _ = zip(*self.state_history[-2:])
            self.ax.plot(xs, ys, c=(0, 0, 1), linestyle='dashed')

        # represent car with an arrow pointing along its heading
        arrow_length = 0.1
        c = np.cos(state[StateIndices.HEADING])
        s = np.sin(state[StateIndices.HEADING])
        dx = arrow_length * c
        dy = arrow_length * s
        car_artists.append(
            plt.arrow(state[StateIndices.X], state[StateIndices.Y], dx, dy, width=arrow_length / 10, ec=color, fc=color,
                      label=name))

        # plot rectangle instead of point to represent robot
        # car_artists.append(plt.scatter(state[StateIndices.X], state[StateIndices.Y], color=c, label=name))
        h = 0.1
        w = 0.15
        offset = np.array([-w / 2, -h / 2])
        rot = np.array([[c, -s],
                        [s, c]])
        offset = rot @ offset
        car_artists.append(plt.Rectangle((state[StateIndices.X] + offset[0],
                                          state[StateIndices.Y] + offset[1]), w, h,
                                         state[StateIndices.HEADING] * 180 / np.pi,
                                         ec=color, fc=color, fill=False))
        self.ax.add_artist(car_artists[-1])

        self.car_artists[name] = car_artists
        if name == 'state':
            self.ax.legend()
        plt.pause(0.05)

    def save_plot(self, filename):
        plt.savefig(filename)

    def true_dynamics(self, state, control):
        """x_{t+1} = f(x_t, u_t) true dynamics function of the car"""
        """The true dynamics should be used as a 'black box' to simulate the car motion"""
        t = 0.1

        next_state = np.copy(state)
        next_state[StateIndices.X] += control[ControlIndices.SPEED] * t * np.cos(state[StateIndices.HEADING])
        next_state[StateIndices.Y] += control[ControlIndices.SPEED] * t * np.sin(state[StateIndices.HEADING])
        next_state[StateIndices.HEADING] += t * control[ControlIndices.TURN]
        return next_state


def run_problem(controls, ABs, start_state, goal_state, speed_limit=(0, 1), turn_limit=(-2, 2), eval=False):
    global bKeepRunning
    car = CarEnvironment(eval)
    state = start_state.copy()

    if not eval:
        car.visualize_state(goal_state, name='goal', color=(0, 0.7, 0), plot_trail=False)
        car.visualize_state(state)

    prediction_error = []

    tol = 1e-10
    bKeepRunning = True

    for i in range(len(controls)):
        if (not bKeepRunning):
            break

        A, B = ABs[i]
        control = controls[i]

        # if control is close to 0, end
        if (np.linalg.norm(control) < tol):
            break

        # use our linearized dynamics to predict next state under this control
        predicted_state = (A @ state) + (B @ control)

        # check that control is within bounds
        if not (speed_limit[0] - tol < control[ControlIndices.SPEED] < speed_limit[1] + tol
                and turn_limit[0] - tol < control[ControlIndices.TURN] < turn_limit[1] + tol):
            raise RuntimeError(
                "Control is out of bounds; optimization constraints may be incorrectly set"
                "\ncontrol: {}\nlimits: {} and {}".format(control, speed_limit, turn_limit))

        state = car.true_dynamics(state, control)
        prediction_error.append(state - predicted_state)
        # print(np.sum((goal_state - predicted_state)**2))
        if not eval:
            car.visualize_state(predicted_state, name='predicted', color=(0.7, 0, 0), plot_trail=False)
            car.visualize_state(state)

    bKeepRunning = False

    prediction_error = np.stack(prediction_error)
    if eval:
        err = np.sum((goal_state - state) ** 2)
        pred_err = np.max(prediction_error)
        if err < 1e-3 and pred_err < 1e-7:
            print("ALL GOOD")
        else:
            print("BAD")
    else:
        car.fig.suptitle('Press Space Bar to Close Program', fontsize=14, fontweight='bold', color='red')
        # car.save_plot(os.path.join(SCRIPT_DIR, "{}.png".format(name)))
        print('Sum squared distance to goal:', np.sum((goal_state - state) ** 2))
        print("max prediction error: {}".format(np.max(prediction_error)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=str)
    parser.add_argument("output", type=str)
    parser.add_argument("--eval", action="store_true")

    args = parser.parse_args()

    with open(args.input, 'r') as f:
        line = f.readline()
        nums = [float(v) for v in line.strip().split()]
        start_state = np.array(nums[:3])
        goal_state = np.array(nums[3:])

    with open(args.output, 'r') as f:
        lines = f.readlines()
        controls = []
        ABs = []
        i = 0
        while i < len(lines):
            u = np.array([float(v) for v in lines[i].strip().split()])
            controls.append(u)
            i += 1
            A = np.array([[float(v) for v in line.strip().split()] for line in lines[i:i + 3]])
            i += 3
            B = np.array([[float(v) for v in line.strip().split()] for line in lines[i:i + 3]])
            i += 3
            ABs.append((A, B))

    # see the difference in average prediction error when the reference control is different
    run_problem(controls, ABs, start_state, goal_state, eval=args.eval)
    if not args.eval:
        # wait until the plot closes
        plt.show(block=True)
