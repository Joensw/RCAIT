#include "classificationresult.h"
#include <utility>

ClassificationResult::ClassificationResult(const QMap<QString, QList<double>> &classificationData,
                                           QList<QString> labels, const QStringList &additionalResults)
        : Result(additionalResults),
          m_classificationData(classificationData),
          m_labels(std::move(labels)) {

    auto tempDir = ProjectManager::getInstance().getProjectImageTempDir();
    auto savable_id = getSavableIdentifier();

    m_classificationGraphics.reset(new ClassificationGraphics(tempDir, savable_id, classificationData));
}

bool ClassificationResult::isValid() const {
    return !m_classificationData.isEmpty() && !m_labels.isEmpty();
}

const QMap<QString, QList<double>> &ClassificationResult::getClassificationData() const {
    return m_classificationData;
}

const QList<QString> &ClassificationResult::getLabels() const {
    return m_labels;
}

const QSharedPointer<ClassificationGraphics> &ClassificationResult::getClassificationGraphics() const {
    return m_classificationGraphics;
}
