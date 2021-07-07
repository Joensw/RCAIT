#include "classificationresult.h"
#include <utility>

ClassificationResult::ClassificationResult(QMap<QString, QList<double>> classificationData,
                                           QList<QString> labels, QList<QImage> additionalResults)
        : Result(std::move(additionalResults)) {

    m_classificationData = std::move(classificationData);
    m_labels = std::move(labels);
}

QMap<QString, QList<double>> ClassificationResult::getClassificationData() {
    return m_classificationData;
}

QList<QString> ClassificationResult::getLabels() {
    return m_labels;
}
