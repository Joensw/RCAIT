# confusion_matrix
import argparse
import ast
import itertools
import sys

import numpy as np
from matplotlib.figure import figaspect
from matplotlib.ticker import MaxNLocator, PercentFormatter
from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt

# No display of plot
plt.ioff()


def plot_top_accuracies_graphics(accdata, identifiers, file):
    np.set_printoptions(precision=2)
    np.set_printoptions(suppress=True)
    # Top accuracy is a (compared runs number) x 2 matrix
    # at least 4 lines of data are required
    print('Top Accuracies data')
    print(accdata)

    # Sort by top1 Accuracy (stable sort)
    accdata = accdata[accdata[:, 0].argsort(kind='mergesort')]

    # Raw data
    top1data = accdata[:, 0]  # 0th column
    top5data = accdata[:, 1]  # 1st column

    # Chart line creation
    ax = plt.figure().gca()
    model_top1s = make_interp_spline(range(len(identifiers)), top1data)
    model_top5s = make_interp_spline(range(len(identifiers)), top5data)
    identifiers_x = np.linspace(1, len(identifiers), 500)
    top1s_y = model_top1s(identifiers_x)
    top5s_y = model_top5s(identifiers_x)

    # Chart line configuration
    plt.plot(identifiers_x, top1s_y, label="Top 1%", color='royalblue', linewidth=4)
    plt.plot(identifiers_x, top5s_y, label="Top 5%", color='orange', linewidth=4)

    # Remove bounding box
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['bottom'].set_visible(False)
    ax.spines['left'].set_visible(False)

    # Remove tickmarks
    plt.tick_params(
        axis='x',  # changes apply to the x-axis
        which='both',  # both major and minor ticks are affected
        bottom=False,  # ticks along the bottom edge are off
        top=False,  # ticks along the top edge are off
        labelbottom=True)  # labels along the bottom edge are on
    plt.tick_params(
        axis='y',  # changes apply to the x-axis
        which='both',  # both major and minor ticks are affected
        left=False,  # ticks along the left edge are off
        right=False,  # ticks along the top edge are off
        labelbottom=True)  # labels along the left edge are on

    # Formatting
    ax.set_xlim([1, len(identifiers)])
    ax.set_ylim([0, 105])
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_formatter(PercentFormatter(100))

    # Ticks and axes
    ax.set_xticklabels(identifiers, rotation=45)

    # Grid
    plt.grid(color='lightgrey', linestyle='-', linewidth=2, axis='y')
    ax.set_axisbelow(True)

    # Labels
    ax.legend(loc="lower center", ncol=2, bbox_to_anchor=(0.5, -0.5), frameon=False)
    plt.ylabel("Accuracy")
    plt.tight_layout()

    plt.savefig(file, format="svg", bbox_inches="tight")
    sys.exit()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a comparison graphic of top accuracies and stores it as '
                                                 'an image.')
    parser.add_argument('accuracies_data', metavar='data',
                        help='Raw table data of the accuracies, formatted as a python array')
    parser.add_argument('row_labels', metavar='labels',
                        help='List of row labels, formatted as python array')
    parser.add_argument('outfile_name', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    data = np.array(ast.literal_eval(args.accuracies_data))
    labels = ast.literal_eval(args.row_labels)
    file_name = args.outfile_name

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'Inter'
    plt.rcParams['font.size'] = 12

    plot_top_accuracies_graphics(data, labels, file_name)
    sys.exit()
