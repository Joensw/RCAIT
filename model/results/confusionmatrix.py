# confusion_matrix
import itertools
import sys
import ast
import numpy as np
import matplotlib.pyplot as plt

plt.ioff()


def plot_confusion_matrix(cm, lbl, file, cmap=plt.cm.get_cmap('CMRmap_r')):
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
    print('Number of arguments:', len(sys.argv), 'arguments.')
    print('Argument List:', str(sys.argv))
    if len(sys.argv) != 4:
        raise TypeError('You need to supply <matrix data>, <matrix labels>, <output file name>')

    matrix = np.array(ast.literal_eval(sys.argv[1]))
    labels = ast.literal_eval(sys.argv[2])
    file_name = sys.argv[3]

    np.set_printoptions(precision=1)

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'SF Pro Text'

    print('Confusion matrix, without normalization')
    print(matrix)
    plot_confusion_matrix(matrix, labels, file_name)
    sys.exit()
