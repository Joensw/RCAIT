_base_ = ['./resnet50.py']
model = dict(
    head = dict(
        num_classes = 2,
        topk = 1,
        cal_acc=True
    ))