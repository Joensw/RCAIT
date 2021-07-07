#include "trainingresult.h"

#include <utility>

TrainingResult::TrainingResult(QMap<int, QPair<double,double>> lossCurveData,
                               ConfusionMatrix *confusionMatrix, QList<QImage> mostMisclassifiedImages,
                               double top1Accuracy, double top5Accuracy, QList<QImage> additionalResults)
        : Result(std::move(additionalResults)) {
    m_lossCurveData = std::move(lossCurveData);
    m_confusionMatrix = confusionMatrix;
    m_mostMisclassifiedImages = std::move(mostMisclassifiedImages);
    m_top1Accuracy = top1Accuracy;
    m_top5Accuracy = top5Accuracy;
}

QMap<int, QPair<double,double>> TrainingResult::getLossCurveData() {
    return m_lossCurveData;
}

ConfusionMatrix *TrainingResult::getConfusionMatrix() const {
    return m_confusionMatrix;
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
