# confusion_matrix
import argparse
import ast
import itertools
import sys

import numpy as np
from matplotlib.ticker import MaxNLocator, FuncFormatter
from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt

# No display of plot
plt.ioff()


def plot_loss_curve(lossdata, file):
    # lossdata is a (epochs) x 3 matrix
    # at least 4 epochs are required
    print('Loss Curve data')
    print(lossdata)

    # Raw data
    epochs = lossdata[:, 0]  # 0th column
    train = lossdata[:, 1] / 100  # 1st column
    validation = lossdata[:, 2] / 100  # 2nd column

    # Chart line creation
    ax = plt.figure().gca()
    model_train = make_interp_spline(epochs, train)
    model_val = make_interp_spline(epochs, validation)
    epochs_x = np.linspace(1, len(epochs), 500)
    train_y = model_train(epochs_x)
    validation_y = model_val(epochs_x)

    # Chart line configuration
    plt.plot(epochs_x, train_y, label="Training", color='royalblue', linewidth=3)
    plt.plot(epochs_x, validation_y, label="Validation", color='orange', linewidth=3)

    # Formatting
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_formatter(FuncFormatter('{0:.0%}'.format))
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
    parser = argparse.ArgumentParser(description='Generates a confusion matrix and stores it as an image.')
    parser.add_argument('lossdata', metavar='data',
                        help='Raw point data for train/val curves, formatted as a python array')
    parser.add_argument('outfilename', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    data = np.array(ast.literal_eval(args.lossdata))
    file_name = args.outfilename

    np.set_printoptions(precision=1)

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'SF Pro Text'
    plt.rcParams['font.size'] = 12

    plot_loss_curve(data, file_name)
    sys.exit()
