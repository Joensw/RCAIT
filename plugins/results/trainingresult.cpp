#include "trainingresult.h"

#include <utility>

TrainingResult::TrainingResult(QMap<int, QPair<double,double>> lossCurve,
                               QAbstractTableModel *confusionMatrix, const QStringList& classLabels, QList<QImage> mostMisclassifiedImages,
                               double top1Accuracy, double top5Accuracy, QList<QImage> additionalResults)
        : Result(std::move(additionalResults)) {
    m_lossCurve = std::move(lossCurve);
    m_confusionMatrix = confusionMatrix;
    m_classLabels = classLabels;
    m_mostMisclassifiedImages = std::move(mostMisclassifiedImages);
    m_top1Accuracy = top1Accuracy;
    m_top5Accuracy = top5Accuracy;
}

QMap<int, QPair<double,double>> TrainingResult::getLossCurve() {
    return m_lossCurve;
}

QAbstractTableModel *TrainingResult::getConfusionMatrix() {
    return m_confusionMatrix;
}

const QStringList &TrainingResult::getClassLabels() const {
    return m_classLabels;
}

const QList<QImage> &TrainingResult::getMostMisclassifiedImages() const {
    return m_mostMisclassifiedImages;
}

double TrainingResult::getTop1Accuracy() const {
    return m_top1Accuracy;
}

double TrainingResult::getTop5Accuracy() const {
    return m_top5Accuracy;
}
