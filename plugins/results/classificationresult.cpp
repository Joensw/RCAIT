#include "classificationresult.h"
#include <utility>

ClassificationResult::ClassificationResult(const QMap<QString, QList<double>> &classificationData,
                                           QList<QString> labels, const QStringList &additionalResults)
        : Result(additionalResults),
          m_classificationData(classificationData) {

    auto& pm = ProjectManager::getInstance();
    m_classificationGraphics = new ClassificationGraphics(pm.getProjectImageTempDir(), this->getIdentifier(), classificationData);
    m_labels = std::move(labels);
}

ClassificationGraphics *ClassificationResult::getClassificationGraphics() const {
    return m_classificationGraphics;
}

const QMap<QString, QList<double>> &ClassificationResult::getClassificationData() const {
    return m_classificationData;
}

const QList<QString> &ClassificationResult::getLabels() const {
    return m_labels;
}
