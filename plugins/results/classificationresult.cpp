#include "classificationresult.h"

ClassificationResult::ClassificationResult(const QString &storageDir,
                                           const QMap<QString, QList<double>> &classificationData,
                                           const QStringList &labels, const QStringList &additionalResults)
        : Result(storageDir, additionalResults),
          m_classificationData(classificationData),
          m_labels(labels) {

    auto savable_id = getSavableIdentifier();

    m_classificationGraphics.reset(new ClassificationGraphics(storageDir, savable_id, classificationData, labels));
}

bool ClassificationResult::isValid() const {
    return !m_classificationData.isEmpty() && !m_labels.isEmpty();
}

const QMap<QString, QList<double>> &ClassificationResult::getClassificationData() const {
    return m_classificationData;
}

const QStringList &ClassificationResult::getLabels() const {
    return m_labels;
}

const QSharedPointer<ClassificationGraphics> &ClassificationResult::getClassificationGraphics() const {
    return m_classificationGraphics;
}
