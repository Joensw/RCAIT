#include "classificationresult.h"
#include <utility>

ClassificationResult::ClassificationResult(const QMap<QString, QList<double>> &classificationData,
                                           QList<QString> labels, const QStringList& additionalResults)
        : Result(additionalResults) {

    m_classificationGraphics = new ClassificationGraphics(this->getIdentifier(), classificationData);
    m_classificationData = classificationData;
    m_labels = std::move(labels);
}

QMap<QString, QList<double>> ClassificationResult::getClassificationData() {
    return m_classificationData;
}

QList<QString> ClassificationResult::getLabels() {
    return m_labels;
}

ClassificationGraphics *ClassificationResult::getClassificationGraphics() const {
    return m_classificationGraphics;
}
