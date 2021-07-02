#ifndef RCAIT_CLASSIFICATIONRESULT_H
#define RCAIT_CLASSIFICATIONRESULT_H


#include <QString>
#include <QMap>
#include <QImage>
#include <QAbstractTableModel>
#include "Result.h"

class ClassificationResult : public Result{
private:
    //Todo: Find Better (Qt?) Datatype
    //QMap<QString, QVector<double>> table;
    QAbstractTableModel *table;
    //Todo: Probably useless
    QVector<QString> labels;
public:
    ClassificationResult(QMap<QString, QVector<double>> table, QVector<QString> labels, QList<QImage> additionalResults);
    QAbstractTableModel* getTable();
    QVector<QString> getLabel();
};


#endif //RCAIT_CLASSIFICATIONRESULT_H
