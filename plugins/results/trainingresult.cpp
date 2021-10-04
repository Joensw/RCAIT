#include "trainingresult.h"

TrainingResult::TrainingResult(const QString &storageDir, const QMap<int, QPair<double, double>> &accuracyCurveData,
                               const QStringList &classLabels, const QList<int> &confusionMatrixValues,
                               QStringList mostMisclassifiedImages, double top1Accuracy, double top5Accuracy,
                               const QStringList &additionalResults)
        : Result(storageDir, additionalResults),
          m_accuracyCurveData(accuracyCurveData),
          m_classLabels(classLabels),
          m_confusionMatrixValues(confusionMatrixValues),
          m_top1Accuracy(top1Accuracy),
          m_top5Accuracy(top5Accuracy),
          m_mostMisclassifiedImages(std::move(mostMisclassifiedImages)) {

    auto savable_id = getSavableIdentifier();

    m_accCurve.reset(new AccuracyCurve(storageDir, savable_id, accuracyCurveData));
    m_confusionMatrix.reset(new ConfusionMatrix(storageDir, savable_id, classLabels, confusionMatrixValues));
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

bool TrainingResult::isValid() const {
    return !m_accuracyCurveData.isEmpty()
           && !m_classLabels.isEmpty()
           && !m_confusionMatrixValues.isEmpty();
}

const QSharedPointer<AccuracyCurve> &TrainingResult::getAccuracyCurve() const {
    return m_accCurve;
}

const QSharedPointer<ConfusionMatrix> &TrainingResult::getConfusionMatrix() const {
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
