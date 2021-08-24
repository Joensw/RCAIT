# confusion_matrix
import argparse
import ast
import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import font_manager
from matplotlib.figure import figaspect
from matplotlib.ticker import PercentFormatter

# No display of plot
plt.ioff()


def plot_top_accuracies_graphics(accdata, identifiers, file):
    np.set_printoptions(precision=2)
    np.set_printoptions(suppress=True)
    # Top accuracy is a (compared runs number) x 2 matrix
    print('Top Accuracies data')
    print(accdata)

    # Sort by top1 Accuracy (stable sort)
    permutation = accdata[:, 0].argsort(kind='mergesort')
    accdata = accdata[permutation]
    identifiers = identifiers[permutation]

    x = np.arange(len(identifiers))  # the label locations
    width = 0.35  # the width of the bars

    # Raw data
    top1data = accdata[:, 0]  # 1st column
    top5data = accdata[:, 1]  # 2nd column

    w, h = figaspect(1 / 3)
    fig, ax = plt.subplots(figsize=(w, h))

    # Chart line creation
    top1Bars = ax.bar(x - width / 2, top1data, width, label='Top 1%', color='royalblue')
    top5Bars = ax.bar(x + width / 2, top5data, width, label='Top 5%', color='orange')

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
    ax.set_ylim([0, 105])
    ax.yaxis.set_major_formatter(PercentFormatter(100))
    ax.set_xticks(x)
    ax.set_xticklabels(identifiers, rotation=45)

    # Grid
    plt.grid(color='lightgrey', linestyle='-', linewidth=2, axis='y')
    ax.set_axisbelow(True)

    # Labels
    ax.bar_label(top1Bars, padding=3)
    ax.bar_label(top5Bars, padding=3)
    ax.legend(loc="lower left", ncol=1, bbox_to_anchor=(-0.05, -0.3), frameon=True)
    plt.ylabel("Accuracy")
    fig.tight_layout()

    plt.savefig(file, format="svg", bbox_inches="tight")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a comparison graphic of top accuracies and stores it as '
                                                 'an image.')
    parser.add_argument('accuracies_data', metavar='data',
                        help='Raw table data of the accuracies, formatted as a python array')
    parser.add_argument('row_labels', metavar='labels', type=str,
                        help='List of row labels, formatted as python array')
    parser.add_argument('outfile_name', metavar='outfile', type=str,
                        help='Output file name including extension')

    args = parser.parse_args()
    data = np.array(ast.literal_eval(args.accuracies_data))
    labels = np.array(ast.literal_eval(args.row_labels))
    file_name = args.outfile_name

    # specify the custom font to use
    font_path = os.path.join(os.path.dirname(__file__), 'Inter-Regular.otf')
    font_manager.fontManager.addfont(font_path)
    prop = font_manager.FontProperties(fname=font_path)
    family = str(prop.get_family()[0])
    plt.rcParams['font.family'] = family
    plt.rcParams['font.{}'.format(family)] = str(prop.get_name())
    plt.rcParams['font.size'] = 12

    plot_top_accuracies_graphics(data, labels, file_name)
