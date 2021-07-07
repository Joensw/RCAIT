#ifndef RCAIT_CLASSIFICATIONRESULT_H
#define RCAIT_CLASSIFICATIONRESULT_H


#include <QString>
#include <QMap>
#include <QImage>
#include "result.h"

class ClassificationResult : public Result {
private:
    QMap<QString, QList<double>> m_classificationData;
    QList<QString> m_labels;
public:
    ClassificationResult(QMap<QString, QList<double>> classificationData,
                         QList<QString> labels, QList<QImage> additionalResults);

    QMap<QString, QList<double>> getClassificationData();

    QList<QString> getLabels();
};


#endif //RCAIT_CLASSIFICATIONRESULT_H
