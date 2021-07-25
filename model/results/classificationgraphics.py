import argparse
import ast

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.offsetbox import AnnotationBbox, OffsetImage

# No display of plot
plt.ioff()


def load_image(fullpath):
    im = plt.imread(fullpath)
    return im


def offset_image(fullpath, ax, y, x=0):
    img = load_image(fullpath)
    im = OffsetImage(img, zoom=0.03)
    im.image.axes = ax

    ab = AnnotationBbox(im, (x, y), xybox=(-25, 0), frameon=False,
                        xycoords='data', boxcoords="offset points", pad=0)

    ax.add_artist(ab)


def plot_classification_graphics(data, paths, category_names, file):
    num_rows = len(paths)
    data_cum = data.cumsum(axis=1)
    category_colors = plt.get_cmap('magma')(
        np.linspace(0.15, 0.85, data.shape[1]))

    fig, ax = plt.subplots(figsize=(7, num_rows))
    ax.invert_yaxis()
    plt.yticks(range(num_rows))
    ax.tick_params(labelleft=False)
    ax.xaxis.set_visible(False)
    ax.set_xlim(0, np.sum(data, axis=1).max(initial=0))

    for i, (colname, color) in enumerate(zip(category_names, category_colors)):
        widths = data[:, i]
        starts = data_cum[:, i] - widths
        rects = ax.barh(range(num_rows), widths, left=starts, height=0.5,
                        label=colname, color=color)

        r, g, b, _ = color
        text_color = 'white' if r * g * b < 0.5 else 'darkgrey'
        ax.bar_label(rects, label_type='center', color=text_color)
    ax.legend(ncol=len(category_names), bbox_to_anchor=(0, 1),
              loc='lower left', fontsize='small')

    ax.tick_params(axis='y', which='major', pad=26)

    for y, path in enumerate(paths):
        offset_image(path, ax, y)

    plt.savefig(file, format="svg", bbox_inches="tight")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a comparison graphic of the classified images and stores '
                                                 'it as an image.')
    parser.add_argument('classification_data', metavar='data',
                        help='Raw table data of the classified images, formatted as a python array')
    parser.add_argument('image_paths', metavar='labels',
                        help='List of all image paths, formatted as python array')
    parser.add_argument('class_labels', metavar='labels',
                        help='List of row labels, formatted as python array')
    parser.add_argument('outfile_name', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    values = np.array(ast.literal_eval(args.classification_data))
    image_paths = np.array(ast.literal_eval(args.image_paths))
    labels = np.array(ast.literal_eval(args.row_labels))
    file_name = args.outfile_name

    # specify the custom font to use
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = 'Inter'
    plt.rcParams['font.size'] = 12

    plot_classification_graphics(values, image_paths, labels, file_name)
