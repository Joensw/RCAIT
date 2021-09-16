# Check imports
try:
    import argparse
    import sys
    import ast
    import os

    import matplotlib.pyplot as plt
    import numpy as np
    from PIL import Image
    from matplotlib import font_manager
    from matplotlib import transforms
    from matplotlib.gridspec import GridSpec
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)

# No display of plot
plt.ioff()


def crop_max_square(pil_img):
    return crop_center(pil_img, min(pil_img.size), min(pil_img.size))


def crop_center(pil_img, crop_width, crop_height):
    img_width, img_height = pil_img.size
    return pil_img.crop(((img_width - crop_width) // 2,
                         (img_height - crop_height) // 2,
                         (img_width + crop_width) // 2,
                         (img_height + crop_height) // 2))


def plot_classification_graphics(data, paths, category_names, file):
    # Numeric settings
    np.set_printoptions(precision=2)
    np.set_printoptions(suppress=True)
    data = data.astype('float') / data.sum(axis=1)[:, np.newaxis] * 100
    num_rows, num_cols = data.shape
    zones = 8

    data_cum = data.cumsum(axis=1)
    category_colors = plt.get_cmap('magma')(
        np.linspace(0.15, 0.85, data.shape[1]))

    # Adjust proportions
    fig = plt.figure(constrained_layout=False, figsize=(21, num_rows * 2))
    gs = GridSpec(num_rows, zones, figure=fig)
    plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0.12)

    for i in range(num_rows):
        im = Image.open(paths[i])

        # Crop the center of the image
        cropped = crop_max_square(im)
        ax_image = fig.add_subplot(gs[i, 0:1])
        ax_chart = fig.add_subplot(gs[i, 1:])
        ax_image.imshow(cropped, extent=[0, 100, 0, 100])

        # Remove ticks and axes from the figure
        ax_image.set_xticks([])
        ax_image.set_yticks([])
        ax_chart.set_xticks([])
        ax_chart.set_yticks([])
        ax_chart.axis("off")

        # Place barcharts
        for j, (colname, color) in enumerate(zip(category_names, category_colors)):
            width = data[i, j]
            start = data_cum[i, j] - width
            if width == 0:
                # Dont stack empty bars because they are bugged
                ax_chart.barh(y=1, width=0, height=1, label=colname, color=color)
            else:
                rects = ax_chart.barh(y=1, width=width, left=start, height=1,
                                      label=colname, color=color)
                r, g, b, _ = color
                if width >= 5:
                    text_color = 'white' if r * g * b < 0.3 else 'black'
                    ax_chart.bar_label(rects, fmt='%.0f%%', label_type='center', color=text_color, fontsize='30')

    # Add one legend for all bars, which supports auto wrapping of the legend
    place_legend_intelligent(category_names, fig)
    # Save result
    plt.savefig(file, format="svg", bbox_inches="tight")


def place_legend_intelligent(category_names, fig):
    ncol = 1
    lgwidth_old = 0.
    renderer = fig.canvas.get_renderer()
    while ncol <= len(category_names):
        lg = plt.legend(bbox_to_anchor=[0, 1, 1, 0],
                        loc='lower left',
                        bbox_transform=plt.gcf().transFigure, borderaxespad=1, ncol=ncol, fontsize='30')
        fig.canvas.draw()
        lgbbox = lg.get_window_extent(renderer).transformed(plt.gca().transAxes.inverted())

        if lgwidth_old == lgbbox.width:
            # All the entries fit within a single row. Keep the legend
            # as is and break the loop.
            ncol -= 1
            break

        if lgbbox.width < 1:
            # The width of the legend is still smaller than that of the axe.
            # Continue iterating.
            ncol += 1
            lgwidth_old = lgbbox.width
        else:
            # The width of the legend is larger than that of the axe.
            # Backtrack ncol, plot the legend so it span the entire width of
            # the axe, and break the loop.
            ncol -= 1
            lg = plt.legend(bbox_to_anchor=[0, 1, 1, 0],
                            loc='lower left',
                            bbox_transform=plt.gcf().transFigure, borderaxespad=1, ncol=ncol,
                            fontsize='30')
            break


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a comparison graphic of the classified images and stores '
                                                 'it as an image.')
    parser.add_argument('classification_data', metavar='data',
                        help='Raw table data of the classified images, formatted as a python array')
    parser.add_argument('image_paths', metavar='paths',
                        help='List of all image paths, formatted as python array')
    parser.add_argument('class_labels', metavar='classes',
                        help='List of row labels, formatted as python array')
    parser.add_argument('outfile_name', metavar='outfile',
                        help='Output file name including extension')

    args = parser.parse_args()
    values = np.array(ast.literal_eval(args.classification_data))
    image_paths = np.array(ast.literal_eval(args.image_paths))
    classes = np.array(ast.literal_eval(args.class_labels))
    file_name = args.outfile_name

    # specify the custom font to use
    font_path = os.path.join(os.path.dirname(__file__), 'Inter-Regular.otf')
    font_manager.fontManager.addfont(font_path)
    prop = font_manager.FontProperties(fname=font_path)
    family = str(prop.get_family()[0])
    plt.rcParams['font.family'] = family
    plt.rcParams['font.{}'.format(family)] = str(prop.get_name())
    plt.rcParams['font.size'] = 12

    plot_classification_graphics(values, image_paths, classes, file_name)
