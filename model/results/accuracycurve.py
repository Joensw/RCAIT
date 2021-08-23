# confusion_matrix
import argparse
import ast
import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import font_manager
from matplotlib.ticker import MaxNLocator, PercentFormatter
from scipy.interpolate import make_interp_spline

# No display of plot
plt.ioff()


def plot_acc_curve(accdata, file):
    np.set_printoptions(precision=2)
    np.set_printoptions(suppress=True)
    # accdata is a (iterations) x 3 matrix
    print('Accuracy Curve data')
    print(accdata)

    # Raw data
    iterations = accdata[:, 0]  # 0th column
    train = accdata[:, 1]  # 1st column
    validation = accdata[:, 2]  # 2nd column

    # Chart line creation
    ax = plt.figure().gca()

    # Default ist k=3. If there are not enough points, choose a smaller k >= 0
    k = max(0, min(len(iterations) - 1, 3))
    model_train = make_interp_spline(iterations, train, k)
    model_val = make_interp_spline(iterations, validation, k)
    iterations_x = np.linspace(1, len(iterations), 500)
    train_y = model_train(iterations_x)
    validation_y = model_val(iterations_x)

    # Chart line configuration
    plt.plot(iterations_x, train_y, label="Training", color='royalblue', linewidth=3)
    plt.plot(iterations_x, validation_y, label="Validation", color='orange', linewidth=3)

    # Formatting
    ax.set_xlim([1, len(iterations)])
    ax.set_ylim([0, 100])
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_formatter(PercentFormatter(100))
    ax.set_aspect(1. / ax.get_data_ratio())

    # Grid
    plt.grid(color='grey', linestyle=':', linewidth=0.7)
    ax.set_axisbelow(True)

    # Labels
    plt.legend(loc="lower right")
    plt.xlabel("Iteration")
    plt.ylabel("Accuracy")
    plt.tight_layout()

    plt.savefig(file, format="svg", bbox_inches="tight")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates an accuracy curve and stores it as an image.')
    parser.add_argument('accdata', metavar='data',
                        help='Raw point data for train/validation curves, formatted as a python array')
    parser.add_argument('outfilename', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    data = np.array(ast.literal_eval(args.accdata))
    file_name = args.outfilename

    # specify the custom font to use
    font_path = os.path.join(os.path.dirname(__file__), 'Inter-Regular.otf')
    font_manager.fontManager.addfont(font_path)
    prop = font_manager.FontProperties(fname=font_path)
    family = str(prop.get_family()[0])
    plt.rcParams['font.family'] = family
    plt.rcParams['font.{}'.format(family)] = str(prop.get_name())
    plt.rcParams['font.size'] = 12

    plot_acc_curve(data, file_name)
