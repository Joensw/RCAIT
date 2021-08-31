# Check imports
try:
    import argparse
    import sys
    import ast
    import os

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
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis] * 100
        print("Normalized confusion matrix")
        plt.imshow(cm, interpolation='nearest', cmap=cmap, vmin=0, vmax=100)
        plt.colorbar(format=PercentFormatter(100))
        decimal = '.1f'
    else:
        print('Confusion matrix, without normalization')
        plt.imshow(cm, interpolation='nearest', cmap=cmap)
        plt.colorbar()
        decimal = '.0f'
    print(cm)
    plt.xticks(range(len(lbl)), lbl, rotation=45)
    plt.yticks(range(len(lbl)), lbl)

    thresh = cm.max() / 2.
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, format(cm[i, j], decimal),
                 horizontalalignment="center",
                 verticalalignment="center",
                 color="white" if cm[i, j] > thresh else "black")

    plt.tight_layout()
    plt.ylabel('True label')
    plt.xlabel('Predicted label')
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
