# confusion_matrix
import argparse
import ast
import sys

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator, PercentFormatter
from scipy.interpolate import make_interp_spline

# No display of plot
plt.ioff()


def plot_loss_curve(lossdata, file):
    np.set_printoptions(precision=2)
    np.set_printoptions(suppress=True)
    # lossdata is a (epochs) x 3 matrix
    print('Loss Curve data')
    print(lossdata)

    # Raw data
    epochs = lossdata[:, 0]  # 0th column
    train = lossdata[:, 1]  # 1st column
    validation = lossdata[:, 2]  # 2nd column

    # Chart line creation
    ax = plt.figure().gca()

    # Default ist k=3. If there are not enough points, choose a smaller k >= 0
    model_train = make_interp_spline(epochs, train, k=max(0, min(len(epochs) - 1, 3)))
    model_val = make_interp_spline(epochs, validation, k=max(0, min(len(epochs) - 1, 3)))
    epochs_x = np.linspace(1, len(epochs), 500)
    train_y = model_train(epochs_x)
    validation_y = model_val(epochs_x)

    # Chart line configuration
    plt.plot(epochs_x, train_y, label="Training", color='royalblue', linewidth=3)
    plt.plot(epochs_x, validation_y, label="Validation", color='orange', linewidth=3)

    # Formatting
    ax.set_xlim([1, len(epochs)])
    ax.set_ylim([0, 100])
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_formatter(PercentFormatter(100))
    ax.set_aspect(1. / ax.get_data_ratio())

    # Grid
    plt.grid(color='grey', linestyle=':', linewidth=0.7)
    ax.set_axisbelow(True)

    # Labels
    plt.legend(loc="upper right")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.tight_layout()

    plt.savefig(file, format="svg", bbox_inches="tight")
    sys.exit()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a loss curve and stores it as an image.')
    parser.add_argument('lossdata', metavar='data',
                        help='Raw point data for train/validation curves, formatted as a python array')
    parser.add_argument('outfilename', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    data = np.array(ast.literal_eval(args.lossdata))
    file_name = args.outfilename

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'Inter'
    plt.rcParams['font.size'] = 12

    plot_loss_curve(data, file_name)
    sys.exit()
