_base_ = ['./imagenet_bs32.py']
dataset_type = 'ImageNet'
img_norm_cfg = dict(
    mean=[123.675, 116.28, 103.53], std=[58.395, 57.12, 57.375], to_rgb=True)
albu_transforms = [dict(type='ColorJitter')]
train_pipeline = [
    dict(type='LoadImageFromFile'),
    dict(type='RandomResizedCrop', scale=(0.8, 1.0), size=224),
    dict(type='RandomFlip', flip_prob=0.5, direction='horizontal'),
    dict(type='RandomErasing'),
    dict(type='Albu', transforms=albu_transforms),
    dict(type='Normalize', **img_norm_cfg),
    dict(type='ImageToTensor', keys=['img']),
    dict(type='ToTensor', keys=['gt_label']),
    dict(type='Collect', keys=['img', 'gt_label'])
]
test_pipeline = [
    dict(type='LoadImageFromFile'),
    dict(type='Resize', size=(256, -1)),
    dict(type='CenterCrop', crop_size=224),
    dict(type='Normalize', **img_norm_cfg),
    dict(type='ImageToTensor', keys=['img']),
    dict(type='Collect', keys=['img'])
]
data = dict(
    # Modify the number of workers according to your computer
    samples_per_gpu = 32,
    workers_per_gpu=2,
    # Specify the path to training set
    train = dict(
        type = dataset_type,
        data_prefix = 'path to training set',
        pipeline=train_pipeline
    ),
    # Specify the path to validation set
    val = dict(
        type = dataset_type,
        data_prefix = 'path to validation set',
        pipeline=test_pipeline
    ),
    # Specify the path to test set
    test = dict(
        type = 'LexicographicallySorted',
        data_prefix = 'path to test set',
        pipeline = test_pipeline
    )
)
# Modify the metric method
evaluation = dict(interval=1000, metric=['accuracy','support'])
