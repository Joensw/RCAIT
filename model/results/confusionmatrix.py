# confusion_matrix
import argparse
import ast
import itertools
import sys

import matplotlib.pyplot as plt
import numpy as np

plt.ioff()


def plot_confusion_matrix(cm, lbl, file, normalize=False, cmap=plt.cm.get_cmap('CMRmap_r')):
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
        print("Normalized confusion matrix")
    else:
        print('Confusion matrix, without normalization')
    print(cm)
    plt.imshow(cm, interpolation='nearest', cmap=cmap)
    plt.colorbar()
    plt.xticks(range(len(lbl)), lbl, rotation=45)
    plt.yticks(range(len(lbl)), lbl)

    thresh = cm.max() / 2.
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, format(cm[i, j], '.1f'),
                 horizontalalignment="center",
                 verticalalignment="center",
                 color="white" if cm[i, j] > thresh else "black")

    plt.tight_layout()
    plt.ylabel('True label')
    plt.xlabel('Predicted label')
    plt.savefig(file, format="svg")
    sys.exit()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a confusion matrix and stores it as an image.')
    parser.add_argument('matrixdata', metavar='data', required=True,
                        help='Raw number content of the matrix, formatted as a python array')
    parser.add_argument('matrixlabels', metavar='labels', required=True,
                        help='List of class labels, formatted as python array')
    parser.add_argument('outfilename', metavar='outfile', required=True,
                        help='Output file name including extension')
    parser.add_argument('normalized', type=bool, metavar='bool', required=False,
                        help='Whether to produce a normalized matrix or not')

    args = parser.parse_args()
    matrix = np.array(ast.literal_eval(args.matrixdata))
    labels = ast.literal_eval(args.matrixlabels)
    file_name = args.outfilename
    normalized = args.normalized

    np.set_printoptions(precision=1)

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'SF Pro Text'

    plot_confusion_matrix(matrix, labels, file_name, normalized)
    sys.exit()
