import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np


def main():
    infile = "pendulum_output.csv"
    data = np.loadtxt(infile)
    data = data.reshape(-1, 2)

    theta = data[0, 0]

    fig = plt.figure()
    ax = plt.gca()
    l = 0.1
    ax.set_xlim(-2*l, 2*l)
    ax.set_ylim(-2*l, 0)
    ax.set_aspect("equal")
    line = ax.plot([0, np.sin(theta)*l], [0, -np.cos(theta)*l])[0]
    text = ax.text(0, -0.01, "hello")

    def viz_t(t):
        while len(ax.patches) > 0:
            ax.patches.pop()
        theta = data[t, 0]
        line.set_data([0, np.sin(theta)*l], [0, -np.cos(theta)*l])
        circle = plt.Circle((np.sin(theta)*l, -np.cos(theta)*l), 0.025)
        ax.add_patch(circle)
        text.set_text(f"{t=}")

    print(f"n frames {data.shape[0]}")
    anim = FuncAnimation(fig, frames=data.shape[0], func=viz_t, interval=10)
    anim.save("lab12_pendulum.gif", fps=60)
    plt.show()


if __name__ == '__main__':
    main()
