#ifndef CLASSIFICATIONRESULT_H
#define CLASSIFICATIONRESULT_H


#include <QString>
#include <QMap>
#include <QImage>
#include "result.h"
#include <classificationgraphics.h>
#include <projectmanager.h>

class ClassificationResult : public Result {
private:
    QMap<QString, QList<double>> m_classificationData;
    QSharedPointer<ClassificationGraphics> m_classificationGraphics;
    QStringList m_labels;

public:
    ClassificationResult(const QString &storageDir, const QMap<QString, QList<double>> &classificationData,
                         const QStringList &labels, const QStringList &additionalResults = {});

    ClassificationResult(const ClassificationResult &) = delete;

    ClassificationResult &operator=(const ClassificationResult &) = delete;

    [[nodiscard]] const QMap<QString, QList<double>> &getClassificationData() const;

    [[nodiscard]] const QStringList &getLabels() const;

    [[nodiscard]] const QSharedPointer<ClassificationGraphics> &getClassificationGraphics() const;

    [[nodiscard]] bool isValid() const;
};


#endif //CLASSIFICATIONRESULT_H
