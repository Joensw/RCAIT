# Check imports
from mpl_toolkits.axes_grid1 import make_axes_locatable

try:
    import argparse
    import sys
    import ast
    import os

    from textwrap import wrap
    import itertools
    import matplotlib.pyplot as plt
    import numpy as np
    from matplotlib import font_manager
    from matplotlib.ticker import PercentFormatter
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)

# No display of plot
plt.ioff()


def plot_confusion_matrix(cm, lbl, file, normalize, cmap=plt.cm.get_cmap('magma_r')):
    # Calculate chart area size
    leftmargin = 0.5  # inches
    rightmargin = 0.5  # inches
    categorysize = 0.5  # inches
    figwidth = leftmargin + rightmargin + (len(lbl) * categorysize)

    f = plt.figure(figsize=(figwidth, figwidth))

    # Create an axes instance and adjust the subplot size
    ax = f.add_subplot(111)
    ax.set_aspect(1)
    f.subplots_adjust(left=leftmargin / figwidth, right=1 - rightmargin / figwidth, top=0.94, bottom=0.1)

    # Label auto wrapping and scaling
    lbl = ['\n'.join(wrap(label, 15)) for label in lbl]
    lbl_fontsize = plt.rcParams['font.size']
    lbl_fontsize -= max(label.count('\n') for label in lbl)
    lbl_fontsize = max(lbl_fontsize, 1)
    plt.ylabel('True label')
    plt.xlabel('Predicted label', labelpad=20)
    ax.xaxis.set_label_position('top')

    # Axis labels and ticks
    ax.set_xticks(range(len(lbl)))
    ax.set_yticks(range(len(lbl)))
    labels = ax.set_xticklabels(lbl, rotation=45, ha='right', fontsize=lbl_fontsize)
    ax.set_yticklabels(lbl, fontsize=lbl_fontsize)

    # create an axis on the right side of ax. The width of cax will be 5%
    # of ax and the padding between cax and ax will be fixed at 0.1 inch.
    divider = make_axes_locatable(ax)
    cax = divider.append_axes("right", size="5%", pad=0.1)

    # Configure normalized and non-normalized mode
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis] * 100
        print("Normalized confusion matrix")
        res = ax.imshow(cm, interpolation='nearest', cmap=cmap, vmin=0, vmax=100)
        plt.colorbar(res, cax=cax, format=PercentFormatter(100))
        decimal = '.1f'
    else:
        print('Confusion matrix, without normalization')
        res = plt.imshow(cm, interpolation='nearest', cmap=cmap)
        plt.colorbar(res, cax=cax)
        decimal = 'd'
    print(cm)

    # Matrix values formatting
    thresh = cm.max() / 2.
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        ax.text(j, i, format(cm[i, j], decimal),
                horizontalalignment="center", verticalalignment="center",
                color="white" if cm[i, j] > thresh else "black")

    # Save graphics
    plt.savefig(file, format="svg", bbox_inches="tight")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a confusion matrix and stores it as an image.')
    parser.add_argument('matrixdata', metavar='data',
                        help='Raw number content of the matrix, formatted as a python array')
    parser.add_argument('matrixlabels', metavar='labels',
                        help='List of class labels, formatted as python array')
    parser.add_argument('outfilename', metavar='outfile',
                        help='Output file name including extension')
    parser.add_argument('--normalized', default=False, action="store_true",
                        dest='normalized', help='Whether to produce a normalized matrix or not')

    args = parser.parse_args()
    matrix = np.array(ast.literal_eval(args.matrixdata))
    labels = ast.literal_eval(args.matrixlabels)
    file_name = args.outfilename
    normalized = args.normalized

    np.set_printoptions(precision=1)

    # specify the custom font to use
    font_path = os.path.join(os.path.dirname(__file__), 'Inter-Regular.otf')
    font_manager.fontManager.addfont(font_path)
    prop = font_manager.FontProperties(fname=font_path)
    family = str(prop.get_family()[0])
    plt.rcParams['font.family'] = family
    plt.rcParams['font.{}'.format(family)] = str(prop.get_name())
    plt.rcParams['font.size'] = 12

    plot_confusion_matrix(matrix, labels, file_name, normalized)
