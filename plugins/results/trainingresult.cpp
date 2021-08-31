#include "trainingresult.h"

#include <utility>

TrainingResult::TrainingResult(const QMap<int, QPair<double, double>> &accuracyCurveData,
                               const QStringList &classLabels, const QList<int> &confusionMatrixValues,
                               QStringList mostMisclassifiedImages, double top1Accuracy, double top5Accuracy,
                               const QStringList &additionalResults)
        : Result(additionalResults),
          m_accuracyCurveData(accuracyCurveData),
          m_classLabels(classLabels),
          m_confusionMatrixValues(confusionMatrixValues),
          m_top1Accuracy(top1Accuracy),
          m_top5Accuracy(top5Accuracy) {

    auto &pm = ProjectManager::getInstance();
    auto tempDir = pm.getProjectImageTempDir();
    auto savable_id = getSavableIdentifier();

    m_accCurve = new AccuracyCurve(tempDir, savable_id, accuracyCurveData);
    m_confusionMatrix = new ConfusionMatrix(tempDir, savable_id, classLabels, confusionMatrixValues);
    m_mostMisclassifiedImages = std::move(mostMisclassifiedImages);
}

const QMap<int, QPair<double, double>> &TrainingResult::getAccuracyCurveData() const {
    return m_accuracyCurveData;
}

const QStringList &TrainingResult::getClassLabels() const {
    return m_classLabels;
}

const QList<int> &TrainingResult::getConfusionMatrixValues() const {
    return m_confusionMatrixValues;
}

bool TrainingResult::isValid()
{
    return !getAccuracyCurveData().isEmpty() && !getClassLabels().isEmpty() && !getConfusionMatrixValues().isEmpty();
}

AccuracyCurve *TrainingResult::getAccuracyCurve() {
    return m_accCurve;
}

ConfusionMatrix *TrainingResult::getConfusionMatrix() const {
    return m_confusionMatrix;
}

QStringList TrainingResult::getMostMisclassifiedImages() const {
    return m_mostMisclassifiedImages;
}

double TrainingResult::getTop1Accuracy() const {
    return m_top1Accuracy;
}

double TrainingResult::getTop5Accuracy() const {
    return m_top5Accuracy;
}
