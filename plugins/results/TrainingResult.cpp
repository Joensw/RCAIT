#include "TrainingResult.h"

TrainingResult::TrainingResult(QList<QImage> additionalResult, QAbstractTableModel *confusionMatrix,
                               QMap<int, QVector<double>> lossCurve, double top1Accuracy, double top5Accuracy,
                               QList<QImage> additionalResults) : Result(additionalResult) {

}

QAbstractTableModel *TrainingResult::getConfusionMatrix() {
    return nullptr;
}

QMap<int, QVector<double>> TrainingResult::getLossCurve() {
    return QMap<int, QVector<double>>();
}

double TrainingResult::getTop1Accuracy() {
    return 0;
}

double TrainingResult::getTop5Accuracy() {
    return 0;
}
