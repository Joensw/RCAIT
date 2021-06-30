#ifndef CLASSIFICATIONRESULT_H
#define CLASSIFICATIONRESULT_H

#include "result.h"

#include <QMap>
#include <QVector>

class ClassificationResult : public Result
{
public:
    ClassificationResult(QMap<QString, QVector<double>> table, QVector<QString> labels, QList<QImage> additionalResults);
    QMap<QString, QVector<double>> getTable();
    QVector<QString> getLabel();

private:
    QMap<QString, QVector<double>> table;
    QVector<QString> labels;
};

#endif // CLASSIFICATIONRESULT_H
