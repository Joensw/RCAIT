#ifndef CLASSIFICATIONRESULT_H
#define CLASSIFICATIONRESULT_H


#include <QString>
#include <QMap>
#include "result.h"
#include <classificationgraphics.h>
#include <projectmanager.h>

/**
 * @brief This class is a specific type of <code>Result</code>.
 * It is also a data retention class and holds all data after a classification process.
 */
class ClassificationResult : public Result {
private:
    QMap<QString, QList<double>> m_classificationData;
    QSharedPointer<ClassificationGraphics> m_classificationGraphics;
    QStringList m_labels;

    ClassificationResult(const ClassificationResult &) = delete;

    ClassificationResult &operator=(const ClassificationResult &) = delete;

public:
    /**
     * @brief Constructs a ClassificationResult.
     * @param storageDir passed to parent, must be a directory path
     * @param classificationData data from the classification, that maps images to their confidence scores.
     * @param labels List of class labels
     * @param additionalResults (Optional) List of paths to additional results.
     */
    ClassificationResult(const QString &storageDir, const QMap<QString, QList<double>> &classificationData,
                         const QStringList &labels, const QStringList &additionalResults = {});

    /**
     * @brief Get the classification data.
     * @return Map of image paths to their corresponding confidence scores.
     */
    [[nodiscard]] const QMap<QString, QList<double>> &getClassificationData() const;

    /**
     * @brief Get the class labels.
     * @return List of class labels.
     */
    [[nodiscard]] const QStringList &getLabels() const;

    /**
     * @brief Get the classification graphics
     * @return shared pointer to the classification graphics of this result
     */
    [[nodiscard]] const QSharedPointer<ClassificationGraphics> &getClassificationGraphics() const;

    /**
     * @brief Checks if this result is valid.
     * @return valid or not.
     */
    [[nodiscard]] bool isValid() const override;
};


#endif //CLASSIFICATIONRESULT_H
