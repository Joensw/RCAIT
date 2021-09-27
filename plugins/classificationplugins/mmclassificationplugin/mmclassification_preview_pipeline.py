# Check imports
try:
    import argparse

    from mmcls.datasets.pipelines.compose import Compose
    import os
    from pathlib import Path

    import mmcv
    from mmcv import Config
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)


def parse_args():
    parser = argparse.ArgumentParser(description='Preview the output of a training pipeline')
    parser.add_argument('config', help='train config file path')
    parser.add_argument('input_dir', help='folder with input images')
    parser.add_argument('output_dir', help='folder to save output images')
    parser.add_argument('num_images', help='number of images that should be processed', type=int, default=-1)
    args = parser.parse_args()
    return args


def retrieve_data_cfg(config_path):
    cfg = Config.fromfile(config_path)
    train_data_cfg = cfg.data.train
    while 'dataset' in train_data_cfg:
        train_data_cfg = train_data_cfg['dataset']
    skip_type = ['DefaultFormatBundle', 'ToTensor', 'Collect']
    train_data_cfg['pipeline'] = [
        x for x in train_data_cfg.pipeline if x['type'] not in skip_type
    ]

    return cfg


def main():
    args = parse_args()
    cfg = retrieve_data_cfg(args.config)

    pipeline = Compose(cfg.data.train.pipeline)

    valid_exts = ('.jpg', '.JPG', '.png', '.PNG')
    images = sorted(filter(lambda x: x.endswith(valid_exts), os.listdir(args.input_dir)))
    if args.num_images >= 0:
        images = images[:args.num_images]

    os.makedirs(args.output_dir, exist_ok=True)

    for img_name in images:
        results = {'img_prefix': args.input_dir, 'img_info': {'filename': img_name}}
        results = pipeline(results)
        img = results['img'].numpy().transpose(1, 2, 0)
        norm_cfg = results['img_norm_cfg']
        denorm_img = mmcv.imdenormalize(img, norm_cfg['mean'], norm_cfg['std'], norm_cfg['to_rgb'])
        mmcv.imwrite(denorm_img, str(Path(args.output_dir) / img_name))


if __name__ == '__main__':
    main()
