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
    ClassificationGraphics* m_classificationGraphics;
    QList<QString> m_labels;
public:
    ClassificationResult(const QMap<QString, QList<double>> &classificationData,
                         QList<QString> labels, const QStringList& additionalResults = {});

    [[nodiscard]] const QMap<QString, QList<double>> &getClassificationData() const;

    [[nodiscard]] const QList<QString> &getLabels() const;

    [[nodiscard]] ClassificationGraphics *getClassificationGraphics() const;

    bool isValid();
};


#endif //CLASSIFICATIONRESULT_H
