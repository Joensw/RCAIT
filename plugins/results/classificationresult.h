#ifndef RCAIT_CLASSIFICATIONRESULT_H
#define RCAIT_CLASSIFICATIONRESULT_H


#include <QString>
#include <QMap>
#include <QImage>
#include "result.h"
#include <classificationgraphics.h>

class ClassificationResult : public Result {
private:
    QMap<QString, QList<double>> m_classificationData;
    ClassificationGraphics* m_classificationGraphics;
    QList<QString> m_labels;
public:
    ClassificationResult(const QMap<QString, QList<double>> &classificationData,
                         QList<QString> labels, const QStringList& additionalResults);

    QMap<QString, QList<double>> getClassificationData() const;

    QList<QString> getLabels() const;

    ClassificationGraphics *getClassificationGraphics() const;
};


#endif //RCAIT_CLASSIFICATIONRESULT_H
